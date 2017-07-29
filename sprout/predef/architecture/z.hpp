/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_Z_HPP
#define SPROUT_PREDEF_ARCHITECTURE_Z_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_Z 0

#if defined(__SYSC_ZARCH__)
#	undef SPROUT_ARCH_Z
#	define SPROUT_ARCH_Z 1
#endif

#if SPROUT_ARCH_Z
#	define SPROUT_ARCH_Z_AVAILABLE
#endif

#define SPROUT_ARCH_Z_NAME "z/Architecture"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_Z_HPP
