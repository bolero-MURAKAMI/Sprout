/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_X86_64_HPP
#define SPROUT_PREDEF_ARCHITECTURE_X86_64_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_X86_64 0

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
#	undef SPROUT_ARCH_X86_64
#	define SPROUT_ARCH_X86_64 1
#endif

#if SPROUT_ARCH_X86_64
#	define SPROUT_ARCH_X86_64_AVAILABLE
#endif

#define SPROUT_ARCH_X86_64_NAME "Intel x86-64"

#include <sprout/predef/architecture/x86.hpp>

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_X86_64_HPP
