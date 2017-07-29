/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_MICROTEC_HPP
#define SPROUT_PREDEF_COMPILER_MICROTEC_HPP

#include <sprout/config.hpp>

#define SPROUT_COMP_MRI 0

#if defined(_MRI)
#	define SPROUT_COMP_MRI_DETECTION 1
#endif

#ifdef SPROUT_COMP_MRI_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_MRI_EMULATED SPROUT_COMP_MRI_DETECTION
#	else
#		undef SPROUT_COMP_MRI
#		define SPROUT_COMP_MRI SPROUT_COMP_MRI_DETECTION
#	endif
#	define SPROUT_COMP_MRI_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_MRI_NAME "Microtec C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_MICROTEC_HPP
