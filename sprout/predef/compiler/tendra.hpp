/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_TENDRA_HPP
#define SPROUT_PREDEF_COMPILER_TENDRA_HPP

#include <sprout/config.hpp>

#define SPROUT_COMP_TENDRA 0

#if defined(__TenDRA__)
#	define SPROUT_COMP_TENDRA_DETECTION 1
#endif

#ifdef SPROUT_COMP_TENDRA_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_TENDRA_EMULATED SPROUT_COMP_TENDRA_DETECTION
#	else
#		undef SPROUT_COMP_TENDRA
#		define SPROUT_COMP_TENDRA SPROUT_COMP_TENDRA_DETECTION
#	endif
#	define SPROUT_COMP_TENDRA_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_TENDRA_NAME "TenDRA C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_TENDRA_HPP
