/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_ARM_HPP
#define SPROUT_PREDEF_ARCHITECTURE_ARM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_ARM 0

#if defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_M_ARM)
#	undef SPROUT_ARCH_ARM
#	if !defined(SPROUT_ARCH_ARM) && defined(__arm64)
#		define SPROUT_ARCH_ARM SPROUT_VERSION_NUMBER(8, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ARM) && defined(__TARGET_ARCH_ARM)
#		define SPROUT_ARCH_ARM SPROUT_VERSION_NUMBER(__TARGET_ARCH_ARM, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ARM) && defined(__TARGET_ARCH_THUMB)
#		define SPROUT_ARCH_ARM SPROUT_VERSION_NUMBER(__TARGET_ARCH_THUMB, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ARM) && defined(_M_ARM)
#		define SPROUT_ARCH_ARM SPROUT_VERSION_NUMBER(_M_ARM, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ARM)
#		define SPROUT_ARCH_ARM 1
#	endif
#endif

#if SPROUT_ARCH_ARM
#	define SPROUT_ARCH_ARM_AVAILABLE
#endif

#define SPROUT_ARCH_ARM_NAME "ARM"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_ARM_HPP
