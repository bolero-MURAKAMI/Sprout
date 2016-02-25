/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_BLACKFIN_HPP
#define SPROUT_PREDEF_ARCHITECTURE_BLACKFIN_HPP

#include <sprout/config.hpp>

#define SPROUT_ARCH_BLACKFIN 0

#if defined(__bfin__) || defined(__BFIN__) || defined(bfin) || defined(BFIN)
#	undef SPROUT_ARCH_BLACKFIN
#	define SPROUT_ARCH_BLACKFIN 1
#endif

#if SPROUT_ARCH_BLACKFIN
#	define SPROUT_ARCH_BLACKFIN_AVAILABLE
#endif

#define SPROUT_ARCH_BLACKFIN_NAME "Blackfin"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_BLACKFIN_HPP
