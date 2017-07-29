/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BSD_FREE_HPP
#define SPROUT_PREDEF_OS_BSD_FREE_HPP

#include <sprout/config.hpp>
#include <sprout/predef/os/bsd.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_OS_BSD_FREE 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__FreeBSD__)
#	ifndef SPROUT_OS_BSD_AVAILABLE
#		define SPROUT_OS_BSD 1
#		define SPROUT_OS_BSD_AVAILABLE
#	endif
#	undef SPROUT_OS_BSD_FREE
#	if defined(__FreeBSD_version)
#		if __FreeBSD_version < 500000
#			define SPROUT_OS_BSD_FREE \
				SPROUT_PREDEF_MAKE_10_VRP000(__FreeBSD_version)
#		else
#			define SPROUT_OS_BSD_FREE \
				SPROUT_PREDEF_MAKE_10_VRR000(__FreeBSD_version)
#		endif
#	else
#		define SPROUT_OS_BSD_FREE 1
#	endif
#endif

#if SPROUT_OS_BSD_FREE
#	define SPROUT_OS_BSD_FREE_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BSD_FREE_NAME "Free BSD"

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_BSDI_HPP
