#!/bin/bash
# =============================================================================
# Copyright (c) 2011-2013 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
stagedir="testspr"
gcc_version="4.7.0 4.7.1 4.7.2 4.7.3 4.8.0 4.8.1"
clang_version="3.2 3.3"
gcc_root="/usr/local"
clang_root="/usr/local"
declare -a user_macros
user_macros=()
declare -a include_paths
include_paths=()
force=0
use_help=0
declare -A version_specific_options
version_specific_options=(
	[clang-3.3]="-ftemplate-depth=512"
)
declare -A results
results=()

compile() {
	echo "${1}-${2} compile..."
	${5}/${1}-${2}/bin/${1/%cc}++ -Wall -pedantic -std=c++11 -o ${stagedir}/test_${1}${2//.} ${4} ${3}
	results[${1}-${2}]=$?
}
execute() {
	if [ ${results[${1}-${2}]} -eq 0 ]; then
		echo "${1}-${2} compile succeeded."
		if ${stagedir}/test_$1${2//.}; then
			echo "${1}-${2} execute succeeded."
		else
			echo >&2 "error: ${1}-${2} execute failed."
		fi
	else
		echo >&2 "error: ${1}-${2} compile failed."
	fi
}

args=`getopt -o S:D:I:f -l stagedir:,gcc-version:,clang-version:,gcc-root:,clang-root:,define:,include:,force,help -- "$@"`
if [ "$?" -ne 0 ]; then
	echo >&2 "error: options parse error. See 'test.sh --help'"
	exit 1
fi
eval set -- ${args}
while [ -n "$1" ]; do
	case $1 in
		-S|--stagedir) stagedir=$2; shift 2;;
		--gcc-version) gcc_version="$2"; shift 2;;
		--clang-version) clang_version="$2"; shift 2;;
		--gcc-root) gcc_root="$2"; shift 2;;
		--clang-root) clang_root="$2"; shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
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
	echo "      --gcc-version=<value>   Indicates gcc version."
	echo "                              Default; '4.7.0 4.7.1 4.7.2 4.7.3 4.8.0 4.8.1'"
	echo ""
	echo "      --clang-version=<value> Indicates clang version."
	echo "                              Default; '3.2 3.3'"
	echo ""
	echo "      --gcc-root=<dir>        Root directory that gcc installed."
	echo "                              Default; '/usr/local'"
	echo ""
	echo "      --clang-root=<dir>      Root directory that clang installed."
	echo "                              Default; '/usr/local'"
	echo ""
	echo "  -D, --define=<identifier>   Define macro for preprocessor."
	echo ""
	echo "  -I, --include=<directory>   Add system include path."
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
echo "  user-macros = (${user_macros[*]})"
echo "  include-paths = (${include_paths[*]})"
echo "  force = ${force}"

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done
for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
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

for version in ${gcc_version}; do
	compile gcc ${version} $(cd $(dirname $0); pwd)/sprout.cpp "${define_options} ${include_options} ${version_specific_options[gcc-${version}]}" ${gcc_root}
done
for version in ${clang_version}; do
	compile clang ${version} $(cd $(dirname $0); pwd)/sprout.cpp "${define_options} ${include_options} ${version_specific_options[clang-${version}]}" ${clang_root}
done

for version in ${gcc_version}; do
	execute gcc ${version}
done
for version in ${clang_version}; do
	execute clang ${version}
done
