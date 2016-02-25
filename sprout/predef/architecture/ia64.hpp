/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_IA64_HPP
#define SPROUT_PREDEF_ARCHITECTURE_IA64_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_IA64 0

#if defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#	undef SPROUT_ARCH_IA64
#	define SPROUT_ARCH_IA64 1
#endif

#if SPROUT_ARCH_IA64
#	define SPROUT_ARCH_IA64_AVAILABLE
#endif

#define SPROUT_ARCH_IA64_NAME "Intel Itanium 64"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_IA64_HPP
