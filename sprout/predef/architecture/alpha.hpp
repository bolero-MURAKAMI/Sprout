/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_ALPHA_HPP
#define SPROUT_PREDEF_ARCHITECTURE_ALPHA_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_ALPHA 0

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#	undef SPROUT_ARCH_ALPHA
#	if !defined(SPROUT_ARCH_ALPHA) && defined(__alpha_ev4__)
#		define SPROUT_ARCH_ALPHA SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ALPHA) && defined(__alpha_ev5__)
#		define SPROUT_ARCH_ALPHA SPROUT_VERSION_NUMBER(5, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ALPHA) && defined(__alpha_ev6__)
#		define SPROUT_ARCH_ALPHA SPROUT_VERSION_NUMBER(6, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_ALPHA)
#		define SPROUT_ARCH_ALPHA 1
#	endif
#endif

#if SPROUT_ARCH_ALPHA
#	define SPROUT_ARCH_ALPHA_AVAILABLE
#endif

#define SPROUT_ARCH_ALPHA_NAME "DEC Alpha"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_ALPHA_HPP
