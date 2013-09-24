#!/usr/bin/env python

import sys
import os
import subprocess
import multiprocessing

def compile(command):
	sys.stdout.write(".")
	sys.stdout.flush()
	return subprocess.call(command, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

if __name__=="__main__":
	argv = sys.argv
	argc = len(argv)

	src = argv[1]
	stagedir = argv[2]
	output = argv[3]
	compiler = argv[4]
	width = int(argv[5])
	height = int(argv[6])
	tile_width = int(argv[7])
	tile_height = int(argv[8])
	compile_options = argv[9]
	darkcult_cpp = argv[10]
	max_procs = int(argv[11])

	commands = []
	for y in range(0, height, tile_height):
		for x in range(0, width, tile_width):
			bin = "%s/%d/%d.out" % (stagedir, y, x)
			out = "%s/%d/%d.ppm" % (stagedir, y, x)
			command = "%s -o %s" \
				" %s" \
				" -DDARKROOM_SOURCE=\'\"%s\"\'" \
				" -DDARKROOM_TOTAL_WIDTH=%d -DDARKROOM_TOTAL_HEIGHT=%d" \
				" -DDARKROOM_TILE_WIDTH=%d -DDARKROOM_TILE_HEIGHT=%d" \
				" -DDARKROOM_OFFSET_X=%d -DDARKROOM_OFFSET_Y=%d" \
				" %s" \
				" && %s > %s" \
				% (compiler, bin,
					compile_options,
					src,
					width, height,
					tile_width, tile_height,
					x, y,
					darkcult_cpp,
					bin, out
				)
			commands.append(command);

	pool = multiprocessing.Pool(max_procs)
	sys.exit(any(pool.map(compile, commands)))
