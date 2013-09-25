#!/bin/bash
# =============================================================================
# Copyright (c) 2011-2013 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
#
# requires: Netpbm (http://netpbm.sourceforge.net/)
#
src="../../example/darkroom/two_spheres.hpp"
stagedir="darkroom"
output="out.ppm"
compiler="g++"
width=16
height=16
tile_width=16
tile_height=16
declare -a user_macros
user_macros=()
declare -a include_paths
include_paths=()
max_procs=1
force=0
use_help=0
darkcult_cpp=$(cd $(dirname $0); pwd)/darkcult.cpp
darkcult_py=$(cd $(dirname $0); pwd)/darkcult.py

args=`getopt -o s:S:o:C:w:h:W:H:D:I:P:f -l source:,stagedir:,output:,compiler:,width:,height:,tile-width:,tile-height:,define:,include:,max-procs:,force,help -- "$@"`
if [ "$?" -ne 0 ]; then
	echo >&2 "error: options parse error. See 'darkcult.sh --help'"
	exit 1
fi
eval set -- ${args}
while [ -n "$1" ]; do
	case $1 in
		-s|--source) src=$2; shift 2;;
		-S|--stagedir) stagedir=$2; shift 2;;
		-o|--output) output=$2; shift 2;;
		-C|--compiler) compiler=$2; shift 2;;
		-w|--width) width=$2; shift 2;;
		-h|--height) height=$2; shift 2;;
		-W|--tile-width) tile_width=$2; shift 2;;
		-H|--tile-height) tile_height=$2; shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
		-P|--max_procs) max_procs=$2; shift 2;;
		-f|--force) force=1; shift;;
		--help) use_help=1; shift;;
		--) shift; break;;
		*) echo >&2 "error: unknown option($1) used."; exit 1;;
	esac
done

if [ ${use_help} -ne 0 ]; then
	echo "help:"
	echo ""
	echo "  -s, --source=<file>         Indicates the source file."
	echo "                              Default; '../../example/darkroom/two_spheres.hpp'"
	echo ""
	echo "  -S, --stagedir=<dir>        Output files here."
	echo "                              Default; 'darkroom'"
	echo ""
	echo "  -o, --output=<file>         Output file of the result."
	echo "                              Default; 'out.ppm'"
	echo ""
	echo "  -C, --compiler=<command>    Compiler to use."
	echo "                              Default; 'g++'"
	echo ""
	echo "  -w, --width=<value>         Output width of rendering."
	echo "                              Default; 16"
	echo ""
	echo "  -h, --height=<value>        Output height of rendering."
	echo "                              Default; 16"
	echo ""
	echo "  -W, --tile-width=<value>    Output width of divided rendering."
	echo "                              Default; 16"
	echo ""
	echo "  -H, --tile-height=<value>   Output height of divided rendering."
	echo "                              Default; 16"
	echo ""
	echo "  -D, --define=<identifier>   Define macro for preprocessor."
	echo ""
	echo "  -I, --include=<dir>         Add system include path."
	echo ""
	echo "  -P, --max-procs=<value>     The maximum number of process use."
	echo "                              Default; 1"
	echo ""
	echo "  -f, --force                 Allow overwrite of <stagedir>."
	echo ""
	echo "      --help                  This message."
	exit 0
fi

echo "settings:"
echo "  source = '${src}'"
echo "  stagedir = '${stagedir}'"
echo "  output = '${output}'"
echo "  compiler = '${compiler}'"
echo "  width = ${width}"
echo "  height = ${height}"
echo "  tile-width = ${tile_width}"
echo "  tile-height = ${tile_height}"
if [ ${#user_macros[*]} -gt 0 ]; then
	echo "  user-macros = (${user_macros[*]})"
fi
if [ ${#include_paths[*]} -gt 0 ]; then
	echo "  include-paths = (${include_paths[*]})"
fi
echo "  max-procs = ${max_procs}"
echo "  force = ${force}"

if [ ! -f "${src}" -a ! -f "$(cd $(dirname $0); pwd)/${src}" ]; then
	echo >&2 "error: source(${src}) not exists."
	exit 1
fi

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

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done

for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
done

for ((y=0; y<height; y+=tile_height)); do
	mkdir -p ${stagedir}/${y}/
done

compile_options="-std=c++11 ${define_options} ${include_options}"

echo "rendering:"
start=${SECONDS}

if [ ${max_procs} -eq 1 ]; then
	for ((y=0; y<height; y+=tile_height)); do
		echo "  y = (${y}/${height})..."
		y_start=${SECONDS}

		echo -n "    x = "
		for ((x=0; x<width; x+=tile_width)); do
			echo -n "(${x}/${height})..."
			binname=${y}/${x}.out
			bin=${stagedir}/${binname}
			${compiler} -o ${bin} \
				${compile_options} \
				-DDARKROOM_SOURCE="\"${src}\"" \
				-DDARKROOM_TOTAL_WIDTH=${width} -DDARKROOM_TOTAL_HEIGHT=${height} \
				-DDARKROOM_TILE_WIDTH=${tile_width} -DDARKROOM_TILE_HEIGHT=${tile_height} \
				-DDARKROOM_OFFSET_X=${x} -DDARKROOM_OFFSET_Y=${y} \
				${darkcult_cpp}
			if [ $? -ne 0 ]; then
				echo ""
				echo >&2 "error: compile(${binname}) failed."
				exit 1
			fi
			${bin} > ${stagedir}/${y}/${x}.ppm
		done
		echo ""

		let "y_elapsed=${SECONDS}-${y_start}"
		echo "    elapsed = ${y_elapsed}s"
	done
else
	echo "  processing in parallel mode."
	echo -n "  "
	python "${darkcult_py}" \
		"${src}" "${stagedir}" "${output}" "${compiler}" \
		"${width}" "${height}" \
		"${tile_width}" "${tile_height}" \
		"${compile_options}" "${darkcult_cpp}" \
		"${max_procs}"
	if [ $? -ne 0 ]; then
		echo ""
		echo >&2 "error: compile failed."
		exit 1
	fi
	echo ""
fi

let "elapsed=${SECONDS}-${start}"
echo "  elapsed(total) = ${elapsed}s"

for ((y=0; y<height; y+=tile_height)); do
	pushd ${stagedir}/${y}/ > /dev/null
#	convert +append $(ls *.ppm | sort -n) ../${y}.ppm
	pnmcat -lr $(ls *.ppm | sort -n) > ../${y}.ppm
	popd > /dev/null
done
pushd ${stagedir} > /dev/null
#convert -append $(ls *.ppm | sort -n) ${output}
pnmcat -tb $(ls *.ppm | sort -n) > ${output}
popd > /dev/null

echo "finished."
