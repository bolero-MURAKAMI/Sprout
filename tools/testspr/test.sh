#!/bin/bash
# =============================================================================
# Copyright (c) 2011-2013 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
#
# requires: Python (http://www.python.org/) if parallel mode
#
stagedir="testspr"
gcc_version="."
clang_version="."
gcc_root="/usr/local"
clang_root="/usr/local"
declare -a user_macros=()
declare -a include_paths=()
max_procs=1
force=0
use_help=0
declare -a common_options=()
declare -a version_options=()
declare -A version_specific_options=(
	[clang-3.3]='-ftemplate-depth=512'
)
test_cpp=$(cd $(dirname $0); pwd)/test.cpp
test_py=$(cd $(dirname $0); pwd)/test.py

args=`getopt -o S:g:c:O:o:D:I:P:f -l stagedir:,gcc-version:,clang-version:,gcc-root:,clang-root:,option:,version-option:,define:,include:,max-procs:,force,help -- "$@"`
if [ "$?" -ne 0 ]; then
	echo >&2 "error: options parse error. See 'test.sh --help'"
	exit 1
fi
eval set -- ${args}
while [ -n "$1" ]; do
	case $1 in
		-S|--stagedir) stagedir=$2; shift 2;;
		-g|--gcc-version) gcc_version="$2"; shift 2;;
		-c|--clang-version) clang_version="$2"; shift 2;;
		--gcc-root) gcc_root="$2"; shift 2;;
		--clang-root) clang_root="$2"; shift 2;;
		-O|--option) common_options=(${common_options[@]} "$2"); shift 2;;
		-o|--version-option) version_options=(${version_options[@]} "$2"); shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
		-P|--max-procs) max_procs=$2; shift 2;;
		-f|--force) force=1; shift;;
		--help) use_help=1; shift;;
		--) shift; break;;
		*) echo >&2 "error: unknown option($1) used."; exit 1;;
	esac
done

if [ ${use_help} -ne 0 ]; then
	echo "help:"
	echo ""
	echo "  -S, --stagedir=<dir>        Output files here."
	echo "                              Default; 'testspr'"
	echo ""
	echo "  -g, --gcc-version=<list>    Indicates gcc version list (space separated)."
	echo "                              If '.', version that is installed on the system."
	echo "                              Default; '.'"
	echo ""
	echo "  -c, --clang-version=<list>  Indicates clang version list (space separated)."
	echo "                              If '.', version that is installed on the system."
	echo "                              Default; '.'"
	echo ""
	echo "      --gcc-root=<dir>        Root directory that gcc installed."
	echo "                              Default; '/usr/local'"
	echo ""
	echo "      --clang-root=<dir>      Root directory that clang installed."
	echo "                              Default; '/usr/local'"
	echo ""
	echo "  -O, --option=<opt>          Add compile option."
	echo ""
	echo "  -o, --version-option=<opt>  Add version specific compile option."
	echo "                              Example; [clang-3.3]='-ftemplate-depth=512'"
	echo ""
	echo "  -D, --define=<identifier>   Define macro for preprocessor."
	echo ""
	echo "  -I, --include=<directory>   Add system include path."
	echo ""
	echo "  -P, --max-procs=<value>     The maximum number of process use."
	echo "                              If other than 1, processing in parallel mode."
	echo "                              If 0, using the number of CPUs in the system."
	echo "                              Default; 1"
	echo ""
	echo "  -f, --force                 Allow overwrite of <stagedir>."
	echo ""
	echo "      --help                  This message."
	exit 0
fi

echo "settings:"
echo "  stagedir = '${stagedir}'"
echo "  gcc-version = (${gcc_version})"
echo "  clang-version = (${clang_version})"
echo "  gcc-root = '${gcc_root}'"
echo "  clang-root = '${clang_root}'"
echo "  common-options = (${common_options[*]})"
echo "  version-options = (${version_options[*]})"
echo "  user-macros = (${user_macros[*]})"
echo "  include-paths = (${include_paths[*]})"
echo "  max-procs = ${max_procs}"
echo "  force = ${force}"

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done
for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
done
compile_options="-Wall -pedantic -std=c++11 ${define_options} ${include_options} ${common_options[*]}"
for option in ${version_options}; do
	eval "version_specific_options${option}"
done

if [ -d "${stagedir}" ]; then
	if [ ${force} -eq 0 ]; then
		echo >&2 "error: stagedir(${stagedir}) already exists."
		exit 1
	else
		rm -f -r ${stagedir}/*
	fi
else
	mkdir -p ${stagedir}
fi

echo "test:"
compile() {
	local base
	if [ ${2} != "." ]; then
		base=${1}-${2}
	else
		base=${1}
	fi
	local bin=${stagedir}/test.${base//.}.out
	local compile_log=${stagedir}/test.${base//.}.compile.log
	local execute_log=${stagedir}/test.${base//.}.execute.log
	local compiler
	if [ ${2} != "." ]; then
		compiler=${6}/${base}/bin/${1/%cc}++
	else
		compiler=${1/%cc}++
	fi
	echo "  compile(${base})..."
	${compiler} -o ${bin} ${4} ${5[${base}]} ${3} >${compile_log} 2>&1
	if [ $? -eq 0 ]; then
		echo "    compile succeeded."
		echo "    execute(${base})..."
		${bin} >${execute_log} 2>&1
		if [ $? -eq 0 ]; then
			echo "      execute succeeded."
		else
			echo >&2 "      error: execute(${base}) failed."
			return 1
		fi
	else
		echo >&2 "    error: compile(${base}) failed."
		return 1
	fi
	return 0
}
if [ ${max_procs} -eq 1 ]; then
	fail_count=0
	for version in ${gcc_version}; do
		compile gcc ${version} ${test_cpp} ${compile_options} ${version_specific_options} ${gcc_root}
		let fail_count=${fail_count}+$?
	done
	for version in ${clang_version}; do
		compile clang ${version} ${test_cpp} ${compile_options} ${version_specific_options} ${clang_root}
		let fail_count=${fail_count}+$?
	done
	if [ ${fail_count} -ne 0 ]; then
		echo >&2 "  error: test(${fail_count}) failed."
	else 
		echo "  test succeeded."
	fi
else
	echo "  processing in parallel mode."
	echo -n "  "
	serialized_version_specific_options={`
		for key in $(echo ${!version_specific_options[@]}); do
			echo \'${key}\':\'${version_specific_options[${key}]}\',
		done
		echo \'_\':\'\'
	`}
	python "${test_py}" \
		"--stagedir=${stagedir}" \
		"--gcc_version=${gcc_version}" "--clang_version=${clang_version}" \
		"--gcc_root=${gcc_root}" "--clang_root=${clang_root}" \
		"--compile_options=${compile_options}" "--test_cpp=${test_cpp}" \
		"--serialized_version_specific_options=${serialized_version_specific_options}" \
		"--max_procs=${max_procs}"
	fail_count=$?
	echo ""
	if [ ${fail_count} -ne 0 ]; then
		echo >&2 "  error: test(${fail_count}) failed."
	else 
		echo "  test succeeded."
	fi
fi

echo "finished."
