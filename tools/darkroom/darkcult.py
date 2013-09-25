#!/usr/bin/env python
# =============================================================================
# Copyright (c) 2011-2013 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
import sys
import optparse
import subprocess
import multiprocessing

def compile(command):
	sys.stdout.write(".")
	sys.stdout.flush()
	return subprocess.call(command, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

def main():
	parser = optparse.OptionParser(description='darkcult.py')
	parser.add_option('--src', type='string')
	parser.add_option('--stagedir', type='string')
	parser.add_option('--output', type='string')
	parser.add_option('--compiler', type='string')
	parser.add_option('--width', type='int')
	parser.add_option('--height', type='int')
	parser.add_option('--tile_width', type='int')
	parser.add_option('--tile_height', type='int')
	parser.add_option('--compile_options', type='string')
	parser.add_option('--darkcult_cpp', type='string')
	parser.add_option('--max_procs', type='int')
	(opts, args) = parser.parse_args()

	pool = multiprocessing.Pool(opts.max_procs if opts.max_procs != 0 else None)

	def format_command(x, y):
		bin = "%s/%d/%d.out" % (opts.stagedir, y, x)
		out = "%s/%d/%d.ppm" % (opts.stagedir, y, x)
		return "%s -o %s" \
			" %s" \
			" -DDARKROOM_SOURCE=\'\"%s\"\'" \
			" -DDARKROOM_TOTAL_WIDTH=%d -DDARKROOM_TOTAL_HEIGHT=%d" \
			" -DDARKROOM_TILE_WIDTH=%d -DDARKROOM_TILE_HEIGHT=%d" \
			" -DDARKROOM_OFFSET_X=%d -DDARKROOM_OFFSET_Y=%d" \
			" %s" \
			" && %s > %s" \
			% (opts.compiler, bin,
				opts.compile_options,
				opts.src,
				opts.width, opts.height,
				opts.tile_width, opts.tile_height,
				x, y,
				opts.darkcult_cpp,
				bin, out
				)
	return any(pool.map(
		compile,
		[format_command(x, y)
			for x in range(0, opts.width, opts.tile_width)
			for y in range(0, opts.height, opts.tile_height)
			]
		))

if __name__=="__main__":
	sys.exit(main())
