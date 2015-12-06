/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_QNXNTO_HPP
#define SPROUT_PREDEF_OS_QNXNTO_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_OS_QNX 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(__QNX__) || defined(__QNXNTO__))
#	undef SPROUT_OS_QNX
#	if !defined(SPROUT_OS_QNX) && defined(_NTO_VERSION)
#		define SPROUT_OS_QNX SPROUT_PREDEF_MAKE_10_VVRR(_NTO_VERSION)
#	endif
#	if !defined(SPROUT_OS_QNX) && defined(__QNX__)
#		define SPROUT_OS_QNX SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_OS_QNX)
#		define SPROUT_OS_QNX 1
#	endif
#endif

#if SPROUT_OS_QNX
#	define SPROUT_OS_QNX_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_QNX_NAME "QNX"

#endif	// #ifndef SPROUT_PREDEF_OS_QNXNTO_HPP
