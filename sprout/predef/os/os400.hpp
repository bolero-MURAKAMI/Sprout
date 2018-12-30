/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_OS400_HPP
#define SPROUT_PREDEF_OS_OS400_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_OS400 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__OS400__)
#	undef SPROUT_OS_OS400
#	define SPROUT_OS_OS400 1
#endif

#if SPROUT_OS_OS400
#	define SPROUT_OS_OS400_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_OS400_NAME "IBM OS/400"

#endif	// #ifndef SPROUT_PREDEF_OS_OS400_HPP
