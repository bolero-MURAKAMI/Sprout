/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_PLATFORM_MINGW_HPP
#define SPROUT_PREDEF_PLATFORM_MINGW_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_PLAT_MINGW 0

#if defined(__MINGW32__) || defined(__MINGW64__)
#	include <_mingw.h>
#	if !defined(SPROUT_PLAT_MINGW_DETECTION) && (defined(__MINGW64_VERSION_MAJOR) && defined(__MINGW64_VERSION_MINOR))
#		define SPROUT_PLAT_MINGW_DETECTION \
			SPROUT_VERSION_NUMBER(__MINGW64_VERSION_MAJOR, __MINGW64_VERSION_MINOR, 0)
#	endif
#	if !defined(SPROUT_PLAT_MINGW_DETECTION) && (defined(__MINGW32_VERSION_MAJOR) && defined(__MINGW32_VERSION_MINOR))
#		define SPROUT_PLAT_MINGW_DETECTION \
			SPROUT_VERSION_NUMBER(__MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION, 0)
#	endif
#	if !defined(SPROUT_PLAT_MINGW_DETECTION)
#		define SPROUT_PLAT_MINGW_DETECTION 1
#	endif
#endif

#ifdef SPROUT_PLAT_MINGW_DETECTION
#	define SPROUT_PLAT_MINGW_AVAILABLE
#	if defined(SPROUT_PREDEF_DETAIL_PLAT_DETECTED)
#		define SPROUT_PLAT_MINGW_EMULATED SPROUT_PLAT_MINGW_DETECTION
#	else
#		undef SPROUT_PLAT_MINGW
#		define SPROUT_PLAT_MINGW SPROUT_PLAT_MINGW_DETECTION
#	endif
#	include <sprout/predef/detail/platform_detected.hpp>
#endif

#define SPROUT_PLAT_MINGW_NAME "MinGW"

#endif	// #ifndef SPROUT_PREDEF_PLATFORM_MINGW_HPP
