/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_PALM_HPP
#define SPROUT_PREDEF_COMPILER_PALM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_PALM 0

#if defined(_PACC_VER)
#	define SPROUT_COMP_PALM_DETECTION SPROUT_PREDEF_MAKE_0X_VRRPP000(_PACC_VER)
#endif

#ifdef SPROUT_COMP_PALM_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_PALM_EMULATED SPROUT_COMP_PALM_DETECTION
#	else
#		undef SPROUT_COMP_PALM
#		define SPROUT_COMP_PALM SPROUT_COMP_PALM_DETECTION
#	endif
#	define SPROUT_COMP_PALM_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_PALM_NAME "Palm C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_PALM_HPP
