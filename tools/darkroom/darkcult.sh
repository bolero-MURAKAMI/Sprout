#!/bin/bash
# =============================================================================
# Copyright (c) 2011-2015 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
#
# requires: Netpbm (http://netpbm.sourceforge.net/)
# requires: Python (http://www.python.org/) if parallel mode
#
src="../../example/darkroom/two_spheres.hpp"
stagedir="darkroom"
output="out.ppm"
compiler="g++"
width=16
height=16
tile_width=16
tile_height=16
l=0
t=0
r=
b=
declare -a common_options=()
declare -a user_macros=()
declare -a include_paths=()
max_procs=
force=0
continuable=0
runtime=0
use_help=0
darkcult_cpp=$(cd $(dirname $0); pwd)/darkcult.cpp
darkcult_py=$(cd $(dirname $0); pwd)/darkcult.py

args=`getopt -o s:S:o:C:w:h:W:H:l:t:r:b:O:D:I:P:fc -l source:,stagedir:,output:,compiler:,width:,height:,tile-width:,tile-height:,left:,top:,right:,bottom:,option:,define:,include:,max-procs:,force,continuable,runtime,help -- "$@"`
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
		-l|--left) l=$2; shift 2;;
		-t|--top) t=$2; shift 2;;
		-r|--right) r=$2; shift 2;;
		-b|--bottom) b=$2; shift 2;;
		-O|--option) common_options=(${common_options[@]} "$2"); shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
		-P|--max-procs) max_procs=$2; shift 2;;
		-f|--force) force=1; shift;;
		-c|--continuable) continuable=1; shift;;
		--runtime) runtime=1; shift;;
		--help) use_help=1; shift;;
		--) shift; break;;
		*) echo >&2 "error: unknown option($1) used."; exit 1;;
	esac
done
: ${r:=${width}}
: ${b:=${height}}

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
	echo "  -l, --left=<value>          Left X position of rendering range."
	echo "                              Default; 0"
	echo ""
	echo "  -t, --top=<value>           Top Y position of rendering range."
	echo "                              Default; 0"
	echo ""
	echo "  -r, --right=<value>         Right X position of rendering range."
	echo "                              Default; <width>"
	echo ""
	echo "  -b, --bottom=<value>        Bottom Y position of rendering range."
	echo "                              Default; <height>"
	echo ""
	echo "  -O, --option=<opt>          Add compile option."
	echo ""
	echo "  -D, --define=<identifier>   Define macro for preprocessor."
	echo ""
	echo "  -I, --include=<dir>         Add system include path."
	echo ""
	echo "  -P, --max-procs=<value>     The maximum number of process use."
	echo "                              If other than null, processing in parallel mode."
	echo "                              If 0, using the number of CPUs in the system."
	echo ""
	echo "  -f, --force                 Allow overwrite of <stagedir>."
	echo ""
	echo "  -c, --continuable           Enable break/continue mode."
	echo "                              Press <Enter>; check finished."
	echo "                              Press 'q'    ; terminate compile."
	echo ""
	echo "      --runtime               Enable runtime mode."
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
echo "  left = ${l}"
echo "  top = ${t}"
echo "  right = ${r}"
echo "  bottom = ${b}"
echo "  user-macros = (${user_macros[*]})"
echo "  include-paths = (${include_paths[*]})"
echo "  max-procs = ${max_procs}"
echo "  force = ${force}"
echo "  continuable = ${continuable}"
echo "  runtime = ${runtime}"

if [ ! -f "${src}" -a ! -f "$(cd $(dirname $0); pwd)/${src}" ]; then
	echo >&2 "error: source(${src}) not exists."
	exit 1
fi

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done
for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
done
compile_options="-std=c++11 ${define_options} ${include_options} ${common_options[*]}"
if [ ${runtime} -ne 0 ]; then
	compile_options="${compile_options} -DDARKROOM_RUNTIME"
fi

if [ -d "${stagedir}" ]; then
	if [ ${force} -eq 0 ]; then
		if [ ${continuable} -eq 0 ]; then
			echo >&2 "error: stagedir(${stagedir}) already exists."
			exit 1
		fi
	else
		rm -f -r ${stagedir}/*
	fi
	rm -f ${stagedir}/*.ppm
else
	mkdir -p ${stagedir}
fi
for ((y=0; y<height; y+=tile_height)); do
	mkdir -p ${stagedir}/${y}/
done

echo "rendering:"
start=${SECONDS}

if [ -z "${max_procs}" ]; then
	for ((y=t; y<b; y+=tile_height)); do
		echo "  y = (${y}/${height})..."
		y_start=${SECONDS}

		echo -n "    x = "
		for ((x=l; x<r; x+=tile_width)); do
			echo -n "(${x}/${height})."
			bin=${stagedir}/${y}/${x}.out
			out=${stagedir}/${y}/${x}.ppm
			${compiler} -o ${bin} \
				${compile_options} \
				-DDARKROOM_SOURCE="\"${src}\"" \
				-DDARKROOM_TOTAL_WIDTH=${width} -DDARKROOM_TOTAL_HEIGHT=${height} \
				-DDARKROOM_TILE_WIDTH=${tile_width} -DDARKROOM_TILE_HEIGHT=${tile_height} \
				-DDARKROOM_OFFSET_X=${x} -DDARKROOM_OFFSET_Y=${y} \
				${darkcult_cpp} \
				&& ${bin} > ${out}
			if [ $? -ne 0 ]; then
				echo ""
				echo >&2 "  error: compile(${y}/${x}) failed."
				exit 1
			fi
		done
		echo ""

		let y_elapsed=${SECONDS}-${y_start}
		echo "    elapsed = ${y_elapsed}s"
	done
else
	echo "  processing in parallel mode."
	if [ ${continuable} -ne 0 ]; then
		echo "  enable break/continue mode."
	fi
	echo -n "  "
	python "${darkcult_py}" \
		"--source=${src}" "--stagedir=${stagedir}" "--output=${output}" "--compiler=${compiler}" \
		"--width=${width}" "--height=${height}" \
		"--tile_width=${tile_width}" "--tile_height=${tile_height}"" "\
		"--left=${l}" "--top=${t}" \
		"--right=${r}" "--bottom=${b}" \
		"--compile_options=${compile_options}" "--darkcult_cpp=${darkcult_cpp}" \
		"--continuable=${continuable}" "--continue_file=${stagedir}/continue.log" \
		"--max_procs=${max_procs}"
	result=$?
	echo ""
	if [ ${result} -eq 2 ]; then
		echo "  compile terminated."
		exit 0
	elif [ ${result} -ne 0 ]; then
		echo >&2 "  error: compile failed."
		exit 1
	fi
fi

let elapsed=${SECONDS}-${start}
echo "  elapsed(total) = ${elapsed}s"

for ((y=0; y<height; y+=tile_height)); do
	pushd ${stagedir}/${y}/ > /dev/null
	pnmcat -lr $(ls *.ppm | sort -n) > ../${y}.ppm
	popd > /dev/null
done
pushd ${stagedir} > /dev/null
pnmcat -tb $(ls *.ppm | sort -n) > ${output}
popd > /dev/null

echo "finished."
