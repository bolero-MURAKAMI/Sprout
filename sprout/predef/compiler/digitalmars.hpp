/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_DIGITALMARS_HPP
#define SPROUT_PREDEF_COMPILER_DIGITALMARS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_DMC 0

#if defined(__DMC__)
#	define SPROUT_COMP_DMC_DETECTION SPROUT_PREDEF_MAKE_0X_VRP(__DMC__)
#endif

#ifdef SPROUT_COMP_DMC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_DMC_EMULATED SPROUT_COMP_DMC_DETECTION
#	else
#		undef SPROUT_COMP_DMC
#		define SPROUT_COMP_DMC SPROUT_COMP_DMC_DETECTION
#	endif
#	define SPROUT_COMP_DMC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_DMC_NAME "Digital Mars"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_DIGITALMARS_HPP
