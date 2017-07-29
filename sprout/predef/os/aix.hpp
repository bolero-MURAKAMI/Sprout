/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_AIX_HPP
#define SPROUT_PREDEF_OS_AIX_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_OS_AIX 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(_AIX) || defined(__TOS_AIX__))
#	undef SPROUT_OS_AIX
#	if !defined(SPROUT_OS_AIX) && defined(_AIX43)
#		define SPROUT_OS_AIX SPROUT_VERSION_NUMBER(4, 3, 0)
#	endif
#	if !defined(SPROUT_OS_AIX) && defined(_AIX41)
#		define SPROUT_OS_AIX SPROUT_VERSION_NUMBER(4, 1, 0)
#	endif
#	if !defined(SPROUT_OS_AIX) && defined(_AIX32)
#		define SPROUT_OS_AIX SPROUT_VERSION_NUMBER(3, 2, 0)
#	endif
#	if !defined(SPROUT_OS_AIX) && defined(_AIX3)
#		define SPROUT_OS_AIX SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_OS_AIX)
#		define SPROUT_OS_AIX 1
#	endif
#endif

#if SPROUT_OS_AIX
#	define SPROUT_OS_AIX_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_AIX_NAME "IBM AIX"

#endif	// #ifndef SPROUT_PREDEF_OS_AIX_HPP
