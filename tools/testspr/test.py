#!/usr/bin/env python
# =============================================================================
# Copyright (c) 2011-2014 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
import sys
import optparse
import subprocess
import multiprocessing

def build(command):
	sys.stdout.write(".")
	sys.stdout.flush()
	return subprocess.call(command, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

def main():
	parser = optparse.OptionParser(description='test.py')
	parser.add_option('--stagedir', type='string', default='testspr')
	parser.add_option('--gcc_version', type='string', default='.')
	parser.add_option('--clang_version', type='string', default='.')
	parser.add_option('--gcc_root', type='string', default='/usr/local')
	parser.add_option('--clang_root', type='string', default='/usr/local')
	parser.add_option('--all_options', type='string', default='')
	parser.add_option('--test_cpp', type='string')
	parser.add_option('--serialized_std_options', type='string', default='{}')
	parser.add_option('--serialized_compiler_specific_options', type='string', default='{}')
	parser.add_option('--serialized_version_specific_options', type='string', default='{}')
	parser.add_option('--max_procs', type='int', default=0)
	(opts, args) = parser.parse_args()

	std_options = eval(opts.serialized_std_options)
	version_specific_options = eval(opts.serialized_version_specific_options)
	compiler_specific_options = eval(opts.serialized_compiler_specific_options)

	def format_command(name, version, root):
		base = "%s-%s" % (name, version) if version != "." else name
		bin = "%s/test.%s.out" % (opts.stagedir, base.replace('.', ''))
		compile_log = "%s/test.%s.compile.log" % (opts.stagedir, base.replace('.', ''))
		execute_log = "%s/test.%s.execute.log" % (opts.stagedir, base.replace('.', ''))
		compiler = "%s/%s/bin/%s++" % (root, base, name.rstrip('c')) if version != "." else "%s++" % name.rstrip('c')
		return "%s -o %s" \
			" %s %s" \
			" %s %s" \
			" %s > %s 2>&1" \
			" && %s > %s 2>&1" \
			% (compiler, bin,
				std_options.get(base, ''), opts.all_options,
				compiler_specific_options.get(name, ''), version_specific_options.get(base, ''),
				opts.test_cpp, compile_log,
				bin, execute_log
				)

	pool = multiprocessing.Pool(opts.max_procs if opts.max_procs != 0 else None)
	return sum(result != 0 for result in pool.map(
		build,
		([format_command('gcc', version, opts.gcc_root)
			for version in opts.gcc_version.split(' ')
			] if opts.gcc_version != ' '
			else []
			)
		+
		([format_command('clang', version, opts.clang_root)
			for version in opts.clang_version.split(' ')
			] if opts.clang_version != ' '
			else []
			)
		))

if __name__ == "__main__":
	sys.exit(main())
