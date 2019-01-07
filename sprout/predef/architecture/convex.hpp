/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_CONVEX_HPP
#define SPROUT_PREDEF_ARCHITECTURE_CONVEX_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_CONVEX 0

#if defined(__convex__)
#	undef SPROUT_ARCH_CONVEX
#	if !defined(SPROUT_ARCH_CONVEX) && defined(__convex_c1__)
#		define SPROUT_ARCH_CONVEX SPROUT_VERSION_NUMBER(1, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_CONVEX) && defined(__convex_c2__)
#		define SPROUT_ARCH_CONVEX SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_CONVEX) && defined(__convex_c32__)
#		define SPROUT_ARCH_CONVEX SPROUT_VERSION_NUMBER(3, 2, 0)
#	endif
#	if !defined(SPROUT_ARCH_CONVEX) && defined(__convex_c34__)
#		define SPROUT_ARCH_CONVEX SPROUT_VERSION_NUMBER(3, 4, 0)
#	endif
#	if !defined(SPROUT_ARCH_CONVEX) && defined(__convex_c38__)
#		define SPROUT_ARCH_CONVEX SPROUT_VERSION_NUMBER(3, 8 ,0)
#	endif
#	if !defined(SPROUT_ARCH_CONVEX)
#		define SPROUT_ARCH_CONVEX 1
#	endif
#endif

#if SPROUT_ARCH_CONVEX
#	define SPROUT_ARCH_CONVEX_AVAILABLE
#endif

#define SPROUT_ARCH_CONVEX_NAME "Convex Computer"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_CONVEX_HPP
