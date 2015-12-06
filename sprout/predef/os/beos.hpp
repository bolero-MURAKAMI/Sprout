/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BEOS_HPP
#define SPROUT_PREDEF_OS_BEOS_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_BEOS 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__BEOS__)
#	undef SPROUT_OS_BEOS
#	define SPROUT_OS_BEOS 1
#endif

#if SPROUT_OS_BEOS
#	define SPROUT_OS_BEOS_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BEOS_NAME "BeOS"

#endif	// #ifndef SPROUT_PREDEF_OS_BEOS_HPP
