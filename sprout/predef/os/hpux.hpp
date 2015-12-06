/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_HPUX_HPP
#define SPROUT_PREDEF_OS_HPUX_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_HPUX 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(hpux) || defined(_hpux) || defined(__hpux))
#	undef SPROUT_OS_HPUX
#	define SPROUT_OS_HPUX 1
#endif

#if SPROUT_OS_HPUX
#	define SPROUT_OS_HPUX_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_HPUX_NAME "HP-UX"

#endif	// #ifndef SPROUT_PREDEF_OS_HPUX_HPP
