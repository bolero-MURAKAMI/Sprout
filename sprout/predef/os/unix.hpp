/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OS_UNIX_HPP
#define SPROUT_PREDEF_OS_UNIX_HPP

#include <sprout/config.hpp>

#define SPROUT_OS_UNIX 0

#if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#	undef SPROUT_OS_UNIX
#	define SPROUT_OS_UNIX 1
#endif

#if SPROUT_OS_UNIX
#	define SPROUT_OS_UNIX_AVAILABLE
#endif

#define SPROUT_OS_UNIX_NAME "Unix Environment"

#define SPROUT_OS_SVR4 0

#if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
#	undef SPROUT_OS_SVR4
#	define SPROUT_OS_SVR4 1
#endif

#if SPROUT_OS_SVR4
#	define SPROUT_OS_SVR4_AVAILABLE
#endif

#define SPROUT_OS_SVR4_NAME "SVR4 Environment"

#endif	// #ifndef SPROUT_PREDEF_OS_UNIX_HPP
