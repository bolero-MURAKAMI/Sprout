/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_RS6K_HPP
#define SPROUT_PREDEF_ARCHITECTURE_RS6K_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_RS6000 0

#if defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2)
#	undef SPROUT_ARCH_RS6000
#	define SPROUT_ARCH_RS6000 1
#endif

#if SPROUT_ARCH_RS6000
#	define SPROUT_ARCH_RS6000_AVAILABLE
#endif

#define SPROUT_ARCH_RS6000_NAME "RS/6000"

#define SPROUT_ARCH_PWR SPROUT_ARCH_RS6000

#if SPROUT_ARCH_PWR
#	define SPROUT_ARCH_PWR_AVAILABLE
#endif

#define SPROUT_ARCH_PWR_NAME SPROUT_ARCH_RS6000_NAME

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_RS6K_HPP
