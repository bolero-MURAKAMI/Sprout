/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_SYS390_HPP
#define SPROUT_PREDEF_ARCHITECTURE_SYS390_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_SYS390 0

#if defined(__s390__) || defined(__s390x__)
#	undef SPROUT_ARCH_SYS390
#	define SPROUT_ARCH_SYS390 1
#endif

#if SPROUT_ARCH_SYS390
#	define SPROUT_ARCH_SYS390_AVAILABLE
#endif

#define SPROUT_ARCH_SYS390_NAME "System/390"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_SYS390_HPP
