/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_DIGNUS_HPP
#define SPROUT_PREDEF_COMPILER_DIGNUS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_SYSC 0

#if defined(__SYSC__)
#	define SPROUT_COMP_SYSC_DETECTION SPROUT_PREDEF_MAKE_10_VRRPP(__SYSC_VER__)
#endif

#ifdef SPROUT_COMP_SYSC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_SYSC_EMULATED SPROUT_COMP_SYSC_DETECTION
#	else
#		undef SPROUT_COMP_SYSC
#		define SPROUT_COMP_SYSC SPROUT_COMP_SYSC_DETECTION
#	endif
#	define SPROUT_COMP_SYSC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_SYSC_NAME "Dignus Systems/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_DIGNUS_HPP
