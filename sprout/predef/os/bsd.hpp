/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_BSD_HPP
#define SPROUT_PREDEF_OS_BSD_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/make.hpp>
#include <sprout/predef/os/macos.hpp>
#include <sprout/predef/os/bsd/bsdi.hpp>
#include <sprout/predef/os/bsd/dragonfly.hpp>
#include <sprout/predef/os/bsd/free.hpp>
#include <sprout/predef/os/bsd/open.hpp>
#include <sprout/predef/os/bsd/net.hpp>

#ifndef SPROUT_OS_BSD
#define SPROUT_OS_BSD 0
#endif

#if !defined(SPROUT_PREDEF_DETAIL_OS_DETECTED) && (defined(BSD) || defined(_SYSTYPE_BSD))
#	undef SPROUT_OS_BSD
#	include <sys/param.h>
#	if !defined(SPROUT_OS_BSD) && defined(BSD4_4)
#		define SPROUT_OS_BSD SPROUT_VERSION_NUMBER(4, 4, 0)
#	endif
#	if !defined(SPROUT_OS_BSD) && defined(BSD4_3)
#		define SPROUT_OS_BSD SPROUT_VERSION_NUMBER(4, 3, 0)
#	endif
#	if !defined(SPROUT_OS_BSD) && defined(BSD4_2)
#		define SPROUT_OS_BSD SPROUT_VERSION_NUMBER(4, 2, 0)
#	endif
#	if !defined(SPROUT_OS_BSD) && defined(BSD)
#		define SPROUT_OS_BSD SPROUT_PREDEF_MAKE_10_VVRR(BSD)
#	endif
#	if !defined(SPROUT_OS_BSD)
#		define SPROUT_OS_BSD 1
#	endif
#endif

#if SPROUT_OS_BSD
#	define SPROUT_OS_BSD_AVAILABLE
#	include <sprout/predef/detail/os_detected.hpp>
#endif

#define SPROUT_OS_BSD_NAME "BSD"

#else	// #ifndef SPROUT_PREDEF_OS_BSD_HPP

#include <sprout/predef/os/bsd/bsdi.hpp>
#include <sprout/predef/os/bsd/dragonfly.hpp>
#include <sprout/predef/os/bsd/free.hpp>
#include <sprout/predef/os/bsd/open.hpp>
#include <sprout/predef/os/bsd/net.hpp>

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_HPP
