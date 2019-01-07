/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_DIAB_HPP
#define SPROUT_PREDEF_COMPILER_DIAB_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_DIAB 0

#if defined(__DCC__)
#	define SPROUT_COMP_DIAB_DETECTION SPROUT_PREDEF_MAKE_10_VRPP(__VERSION_NUMBER__)
#endif

#ifdef SPROUT_COMP_DIAB_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_DIAB_EMULATED SPROUT_COMP_DIAB_DETECTION
#	else
#		undef SPROUT_COMP_DIAB
#		define SPROUT_COMP_DIAB SPROUT_COMP_DIAB_DETECTION
#	endif
#	define SPROUT_COMP_DIAB_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_DIAB_NAME "Diab C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_DIAB_HPP
