/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_MACOS_HPP
#define SPROUT_PREDEF_OS_MACOS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/os/ios.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_OS_MACOS 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
#	undef SPROUT_OS_MACOS
#	if !defined(SPROUT_OS_MACOS) && defined(__APPLE__) && defined(__MACH__)
#		define SPROUT_OS_MACOS SPROUT_VERSION_NUMBER(10, 0, 0)
#	endif
#	if !defined(SPROUT_OS_MACOS)
#		define SPROUT_OS_MACOS SPROUT_VERSION_NUMBER(9, 0, 0)
#	endif
#endif

#if SPROUT_OS_MACOS
#	define SPROUT_OS_MACOS_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_MACOS_NAME "Mac OS"

#endif	// #ifndef SPROUT_PREDEF_OS_MACOS_HPP
