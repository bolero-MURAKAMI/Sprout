/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_ADROID_HPP
#define SPROUT_PREDEF_OS_ADROID_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_ANDROID 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__ANDROID__)
#	undef SPROUT_OS_ANDROID
#	define SPROUT_OS_ANDROID 1
#endif

#if SPROUT_OS_ANDROID
#	define SPROUT_OS_ANDROID_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_ANDROID_NAME "Android"

#endif	// #ifndef SPROUT_PREDEF_OS_ADROID_HPP
