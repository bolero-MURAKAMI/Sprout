/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_IOS_HPP
#define SPROUT_PREDEF_OS_IOS_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_IOS 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__))
#	undef SPROUT_OS_IOS
#	define SPROUT_OS_IOS (__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ * 1000)
#endif

#if SPROUT_OS_IOS
#	define SPROUT_OS_IOS_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_IOS_NAME "iOS"

#endif	// #ifndef SPROUT_PREDEF_OS_IOS_HPP
