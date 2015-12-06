/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_PYRAMID_HPP
#define SPROUT_PREDEF_ARCHITECTURE_PYRAMID_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_PYRAMID 0

#if defined(pyr)
#	undef SPROUT_ARCH_PYRAMID
#	define SPROUT_ARCH_PYRAMID 1
#endif

#if SPROUT_ARCH_PYRAMID
#	define SPROUT_ARCH_PYRAMID_AVAILABLE
#endif

#define SPROUT_ARCH_PYRAMID_NAME "Pyramid 9810"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_PYRAMID_HPP
