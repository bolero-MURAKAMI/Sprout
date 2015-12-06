/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_INTEL_HPP
#define SPROUT_PREDEF_COMPILER_INTEL_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_INTEL 0

#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || \
	defined(__ECC)
#	if !defined(SPROUT_COMP_INTEL_DETECTION) && defined(__INTEL_COMPILER)
#		define SPROUT_COMP_INTEL_DETECTION SPROUT_PREDEF_MAKE_10_VRP(__INTEL_COMPILER)
#	endif
#	if !defined(SPROUT_COMP_INTEL_DETECTION)
#		define SPROUT_COMP_INTEL_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_INTEL_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_INTEL_EMULATED SPROUT_COMP_INTEL_DETECTION
#	else
#		undef SPROUT_COMP_INTEL
#		define SPROUT_COMP_INTEL SPROUT_COMP_INTEL_DETECTION
#	endif
#	define SPROUT_COMP_INTEL_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_INTEL_NAME "Intel C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_INTEL_HPP
