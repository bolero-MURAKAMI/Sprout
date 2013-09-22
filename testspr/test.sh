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
declare -a user_macros
user_macros=()
declare -a include_paths
include_paths=()
force=0
declare -A version_specific_options
version_specific_options=(
	[clang-3.3]="-ftemplate-depth=512"
)

compile() {
	echo ": $1-$2 compile..."
	/usr/local/$1-$2/bin/${1/%cc}++ -Wall -pedantic -std=c++11 -o ${stagedir}/test_$1${2//.} $4 $3
	let "succ_$1${2//.}=$?"
}

execute() {
	if eval [ \$succ_$1${2//.} -eq 0 ]; then
		echo ": $1-$2 compile succeeded."
		if ${stagedir}/test_$1${2//.}; then
			echo ": $1-$2 execute succeeded."
		else
			echo >&2 -e ": \e[31m$1-$2 execute failed.\e[m"
		fi
	else
		echo >&2 -e ": \e[31m$1-$2 compile failed.\e[m"
	fi
}

args=`getopt -o S:D:I:f -l stagedir:,gcc-version:,clang-version:,define:,include:,force -- "$@"`
if [ "$?" -ne 0 ]; then
	echo >&2 -e ": \e[31musage: $0 [-S|--stagedir=path] [--gcc-version=versions] [--clang-version=versions] [-D|--define=identifier]* [-I|--include=path]* [-f|-force]\e[m"
	exit 1
fi
eval set -- ${args}
while [ -n "$1" ]; do
	case $1 in
		-S|--stagedir) stagedir=$2; shift 2;;
		--gcc-version) gcc_version="$2"; shift 2;;
		--clang-version) clang_version="$2"; shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
		-f|--force) force=1; shift;;
		--) shift; break;;
		*) echo >&2 -e ": \e[31munknown option($1) used.\e[m"; exit 1;;
	esac
done
echo ": settings"
echo ":   stagedir = \"${stagedir}\""
echo ":   gcc-version = (${gcc_version})"
echo ":   clang-version = (${clang_version})"
if [ ${#user_macros[*]} -gt 0 ]; then
	echo ":   user-macros = (${user_macros[*]})"
fi
if [ ${#include_paths[*]} -gt 0 ]; then
	echo ":   include-paths = (${include_paths[*]})"
fi
echo ":   force = ${force}"

if [ -d "${stagedir}" ]; then
	if [ ${force} -eq 0 ]; then
		echo >&2 -e ": \e[31mstagedir(${stagedir}) already exists.\e[m"
		exit 1
	else
		rm -f -r ${stagedir}/*
	fi
else
	mkdir -p ${stagedir}
fi

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done

for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
done

for version in ${gcc_version}; do
	compile gcc ${version} $(cd $(dirname $0); pwd)/sprout.cpp "${define_options} ${include_options} ${version_specific_options[gcc-${version}]}"
done

for version in ${clang_version}; do
	compile clang ${version} $(cd $(dirname $0); pwd)/sprout.cpp "${define_options} ${include_options} ${version_specific_options[clang-${version}]}"
done

for version in ${gcc_version}; do
	execute gcc ${version}
done

for version in ${clang_version}; do
	execute clang ${version}
done
