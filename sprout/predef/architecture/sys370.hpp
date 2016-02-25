/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_SYS370_HPP
#define SPROUT_PREDEF_ARCHITECTURE_SYS370_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_SYS370 0

#if defined(__370__) || defined(__THW_370__)
#	undef SPROUT_ARCH_SYS370
#	define SPROUT_ARCH_SYS370 1
#endif

#if SPROUT_ARCH_SYS370
#	define SPROUT_ARCH_SYS370_AVAILABLE
#endif

#define SPROUT_ARCH_SYS370_NAME "System/370"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_SYS370_HPP
