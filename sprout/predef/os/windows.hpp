/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_WINDOWS_HPP
#define SPROUT_PREDEF_OS_WINDOWS_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_WINDOWS 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) \
	&& (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#	undef SPROUT_OS_WINDOWS
#	define SPROUT_OS_WINDOWS 1
#endif

#if SPROUT_OS_WINDOWS
#	define SPROUT_OS_WINDOWS_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_WINDOWS_NAME "Microsoft Windows"

#endif	// #ifndef SPROUT_PREDEF_OS_WINDOWS_HPP
