#!/usr/bin/env python
# =============================================================================
# Copyright (c) 2011-2017 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
import sys
import optparse
import subprocess
import multiprocessing
import logging
import tty

def build(command):
	sys.stdout.write(".")
	sys.stdout.flush()
	return subprocess.call(command, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

def continue_build(command):
	if command[2]:
		sys.stdout.write("*")
		sys.stdout.flush()
		return 0
	sys.stdout.write(".")
	sys.stdout.flush()
	result = subprocess.call(command[0], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	if not result:
		logging.critical(command[1])
	return result

def main():
	parser = optparse.OptionParser(description='darkcult.py')
	parser.add_option('--source', type='string', default='../../example/darkroom/two_spheres.hpp')
	parser.add_option('--stagedir', type='string', default='darkroom')
	parser.add_option('--output', type='string', default='out.ppm')
	parser.add_option('--compiler', type='string', default='g++')
	parser.add_option('--width', type='int', default=16)
	parser.add_option('--height', type='int', default=16)
	parser.add_option('--tile_width', type='int', default=16)
	parser.add_option('--tile_height', type='int', default=16)
	parser.add_option('--left', type='int', default=0)
	parser.add_option('--top', type='int', default=0)
	parser.add_option('--right', type='int')
	parser.add_option('--bottom', type='int')
	parser.add_option('--compile_options', type='string', default='')
	parser.add_option('--darkcult_cpp', type='string')
	parser.add_option('--continuable', type='int', default=0)
	parser.add_option('--continue_file', type='string', default='continue.log')
	parser.add_option('--max_procs', type='int', default=0)
	(opts, args) = parser.parse_args()

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
				opts.source,
				opts.width, opts.height,
				opts.tile_width, opts.tile_height,
				x, y,
				opts.darkcult_cpp,
				bin, out
				)

	if opts.continuable:
		logging.basicConfig(
			filename=opts.continue_file,
			format="%(message)s"
			)
		completed = [line.strip() for line in open(opts.continue_file)]

		fd = sys.stdin.fileno()
		tc_old = tty.tcgetattr(fd)
		tty.setcbreak(fd)

		def format_continue_command(x, y):
			key = "%d %d" % (x, y)
			return (format_command(x, y), key, key in completed)

		pool = multiprocessing.Pool(opts.max_procs if opts.max_procs != 0 else None)
		try:
			results = pool.map_async(
				continue_build,
				[format_continue_command(x, y)
					for y in range(opts.top, opts.bottom, opts.tile_height)
					for x in range(opts.left, opts.right, opts.tile_width)
					]
				)
			while True:
				code = sys.stdin.read(1)
				if results.ready():
					break
				if code == 'q':
					pool.terminate()
					return 2
			return any(results.get())
		finally:
			tty.tcsetattr(fd, tty.TCSADRAIN, tc_old)
			logging.shutdown()
	else:
		pool = multiprocessing.Pool(opts.max_procs if opts.max_procs != 0 else None)
		return any(pool.map(
			build,
			[format_command(x, y)
				for y in range(opts.top, opts.bottom, opts.tile_height)
				for x in range(opts.left, opts.right, opts.tile_width)
				]
			))

if __name__ == "__main__":
	sys.exit(main())
