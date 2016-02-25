/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BSD_NET_HPP
#define SPROUT_PREDEF_OS_BSD_NET_HPP

#include <sprout/config.hpp>
#include <sprout/predef/os/bsd.hpp>
#include <sprout/predef/make.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_OS_BSD_NET 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__NETBSD__) || defined(__NetBSD__)
#	ifndef SPROUT_OS_BSD_AVAILABLE
#		define SPROUT_OS_BSD 1
#		define SPROUT_OS_BSD_AVAILABLE
#	endif
#	undef SPROUT_OS_BSD_NET
#	if defined(__NETBSD__)
#		if defined(__NETBSD_version)
#			if __NETBSD_version < 500000
#				define SPROUT_OS_BSD_NET \
					SPROUT_PREDEF_MAKE_10_VRP000(__NETBSD_version)
#			else
#				define SPROUT_OS_BSD_NET \
					SPROUT_PREDEF_MAKE_10_VRR000(__NETBSD_version)
#			endif
#		else
#			define SPROUT_OS_BSD_NET 1
#		endif
#	elif defined(__NetBSD__)
#		if !defined(SPROUT_OS_BSD_NET) && defined(NetBSD0_8)
#			define SPROUT_OS_BSD_NET SPROUT_VERSION_NUMBER(0, 8, 0)
#		endif
#		if !defined(SPROUT_OS_BSD_NET) && defined(NetBSD0_9)
#			define SPROUT_OS_BSD_NET SPROUT_VERSION_NUMBER(0, 9, 0)
#		endif
#		if !defined(SPROUT_OS_BSD_NET) && defined(NetBSD1_0)
#			define SPROUT_OS_BSD_NET SPROUT_VERSION_NUMBER(1, 0, 0)
#		endif
#		if !defined(SPROUT_OS_BSD_NET) && defined(__NetBSD_Version)
#			define SPROUT_OS_BSD_NET \
				SPROUT_PREDEF_MAKE_10_VVRR00PP00(__NetBSD_Version)
#		endif
#		if !defined(SPROUT_OS_BSD_NET)
#			define SPROUT_OS_BSD_NET 1
#		endif
#	endif
#endif

#if SPROUT_OS_BSD_NET
#	define SPROUT_OS_BSD_NET_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BSD_NET_NAME "DragonFly BSD"

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_NET_HPP
