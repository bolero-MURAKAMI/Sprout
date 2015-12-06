/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_SGI_MIPSPRO_HPP
#define SPROUT_PREDEF_COMPILER_SGI_MIPSPRO_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_SGI 0

#if defined(__sgi) || defined(sgi)
#	if !defined(SPROUT_COMP_SGI_DETECTION) && defined(_SGI_COMPILER_VERSION)
#		define SPROUT_COMP_SGI_DETECTION SPROUT_PREDEF_MAKE_10_VRP(_SGI_COMPILER_VERSION)
#	endif
#	if !defined(SPROUT_COMP_SGI_DETECTION) && defined(_COMPILER_VERSION)
#		define SPROUT_COMP_SGI_DETECTION SPROUT_PREDEF_MAKE_10_VRP(_COMPILER_VERSION)
#	endif
#	if !defined(SPROUT_COMP_SGI_DETECTION)
#		define SPROUT_COMP_SGI_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_SGI_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_SGI_EMULATED SPROUT_COMP_SGI_DETECTION
#	else
#		undef SPROUT_COMP_SGI
#		define SPROUT_COMP_SGI SPROUT_COMP_SGI_DETECTION
#	endif
#	define SPROUT_COMP_SGI_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_SGI_NAME "SGI MIPSpro"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_SGI_MIPSPRO_HPP
