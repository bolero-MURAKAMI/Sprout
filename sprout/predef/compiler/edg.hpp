/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_EDG_HPP
#define SPROUT_PREDEF_COMPILER_EDG_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_EDG 0

#if defined(__EDG__)
#	define SPROUT_COMP_EDG_DETECTION SPROUT_PREDEF_MAKE_10_VRR(__EDG_VERSION__)
#endif

#ifdef SPROUT_COMP_EDG_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_EDG_EMULATED SPROUT_COMP_EDG_DETECTION
#	else
#		undef SPROUT_COMP_EDG
#		define SPROUT_COMP_EDG SPROUT_COMP_EDG_DETECTION
#	endif
#	define SPROUT_COMP_EDG_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_EDG_NAME "EDG C++ Frontend"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_EDG_HPP
