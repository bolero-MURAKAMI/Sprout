/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_X86_HPP
#define SPROUT_PREDEF_ARCHITECTURE_X86_HPP

#include <sprout/config.hpp>
#include <sprout/predef/architecture/x86/32.hpp>
#include <sprout/predef/architecture/x86/64.hpp>

#define SPROUT_ARCH_X86 0

#if SPROUT_ARCH_X86_32 || SPROUT_ARCH_X86_64
#	undef SPROUT_ARCH_X86
#	define SPROUT_ARCH_X86 1
#endif

#if SPROUT_ARCH_X86
#	define SPROUT_ARCH_X86_AVAILABLE
#endif

#define SPROUT_ARCH_X86_NAME "Intel x86"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_X86_HPP
