/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_VMS_HPP
#define SPROUT_PREDEF_OS_VMS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_OS_VMS 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(VMS) || defined(__VMS))
#	undef SPROUT_OS_VMS
#	if defined(__VMS_VER)
#		define SPROUT_OS_VMS SPROUT_PREDEF_MAKE_10_VVRR00PP00(__VMS_VER)
#	else
#		define SPROUT_OS_VMS 1
#	endif
#endif

#if SPROUT_OS_VMS
#	define SPROUT_OS_VMS_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_VMS_NAME "VMS"

#endif	// #ifndef SPROUT_PREDEF_OS_VMS_HPP
