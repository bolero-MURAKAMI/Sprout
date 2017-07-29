/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_COMEAU_HPP
#define SPROUT_PREDEF_COMPILER_COMEAU_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_COMO 0

#if defined(__COMO__)
#	if !defined(SPROUT_COMP_COMO_DETECTION) && defined(__COMO_VERSION__)
#		define SPROUT_COMP_COMO_DETECTION SPROUT_PREDEF_MAKE_0X_VRP(__COMO_VERSION__)
#	endif
#	if !defined(SPROUT_COMP_COMO_DETECTION)
#		define SPROUT_COMP_COMO_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_COMO_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_COMO_EMULATED SPROUT_COMP_COMO_DETECTION
#	else
#		undef SPROUT_COMP_COMO
#		define SPROUT_COMP_COMO SPROUT_COMP_COMO_DETECTION
#	endif
#	define SPROUT_COMP_COMO_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_COMO_NAME "Comeau C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_COMEAU_HPP
