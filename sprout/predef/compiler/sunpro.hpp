/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_SUNPRO_HPP
#define SPROUT_PREDEF_COMPILER_SUNPRO_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_SUNPRO 0

#if defined(__SUNPRO_CC) || defined(__SUNPRO_C)
#	if !defined(SPROUT_COMP_SUNPRO_DETECTION) && defined(__SUNPRO_CC)
#		if (__SUNPRO_CC < 0x5100)
#			define SPROUT_COMP_SUNPRO_DETECTION SPROUT_PREDEF_MAKE_0X_VRP(__SUNPRO_CC)
#		else
#			define SPROUT_COMP_SUNPRO_DETECTION SPROUT_PREDEF_MAKE_0X_VVRRP(__SUNPRO_CC)
#		endif
#	endif
#	if !defined(SPROUT_COMP_SUNPRO_DETECTION) && defined(__SUNPRO_C)
#		if (__SUNPRO_C < 0x5100)
#			define SPROUT_COMP_SUNPRO_DETECTION SPROUT_PREDEF_MAKE_0X_VRP(__SUNPRO_C)
#		else
#			define SPROUT_COMP_SUNPRO_DETECTION SPROUT_PREDEF_MAKE_0X_VVRRP(__SUNPRO_C)
#		endif
#	endif
#	if !defined(SPROUT_COMP_SUNPRO_DETECTION)
#		define SPROUT_COMP_SUNPRO_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_SUNPRO_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_SUNPRO_EMULATED SPROUT_COMP_SUNPRO_DETECTION
#	else
#		undef SPROUT_COMP_SUNPRO
#		define SPROUT_COMP_SUNPRO SPROUT_COMP_SUNPRO_DETECTION
#	endif
#	define SPROUT_COMP_SUNPRO_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_SUNPRO_NAME "Oracle Solaris Studio"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_SUNPRO_HPP
