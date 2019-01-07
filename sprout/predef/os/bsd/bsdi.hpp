/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BSD_BSDI_HPP
#define SPROUT_PREDEF_OS_BSD_BSDI_HPP

#include <sprout/config.hpp>
#include <sprout/predef/os/bsd.hpp>

#define SPROUT_OS_BSD_BSDI 0

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && defined(__bsdi__)
#	ifndef SPROUT_OS_BSD_AVAILABLE
#		define SPROUT_OS_BSD 1
#		define SPROUT_OS_BSD_AVAILABLE
#	endif
#	undef SPROUT_OS_BSD_BSDI
#	define SPROUT_OS_BSD_BSDI 1
#endif

#if SPROUT_OS_BSD_BSDI
#	define SPROUT_OS_BSD_BSDI_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BSD_BSDI_NAME "BSDi BSD/OS"

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_BSDI_HPP
