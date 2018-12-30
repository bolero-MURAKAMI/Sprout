/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BSD_OPEN_HPP
#define SPROUT_PREDEF_OS_BSD_OPEN_HPP

#include <sprout/config.hpp>
#include <sprout/predef/os/bsd.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_OS_BSD_OPEN 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && ( \
	defined(__OpenBSD__) \
	)
#	ifndef SPROUT_OS_BSD_AVAILABLE
#		define SPROUT_OS_BSD 1
#		define SPROUT_OS_BSD_AVAILABLE
#	endif
#	undef SPROUT_OS_BSD_OPEN
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_0)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_1)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 1, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_2)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 2, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_3)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 3, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_4)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 4, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_5)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 5, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_6)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 6, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_7)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 7, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_8)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 8, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD2_9)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(2, 9, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_0)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_1)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 1, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_2)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 2, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_3)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 3, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_4)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 4, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_5)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 5, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_6)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 6, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_7)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 7, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_8)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 8, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD3_9)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(3, 9, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_0)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_1)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 1, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_2)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 2, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_3)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 3, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_4)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 4, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_5)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 5, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_6)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 6, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_7)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 7, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_8)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 8, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN) && defined(OpenBSD4_9)
#		define SPROUT_OS_BSD_OPEN SPROUT_VERSION_NUMBER(4, 9, 0)
#	endif
#	if !defined(SPROUT_OS_BSD_OPEN)
#		define SPROUT_OS_BSD_OPEN 1
#	endif
#endif

#if SPROUT_OS_BSD_OPEN
#	define SPROUT_OS_BSD_OPEN_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BSD_OPEN_NAME "OpenBSD"

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_OPEN_HPP
