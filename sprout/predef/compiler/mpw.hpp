/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_MPW_HPP
#define SPROUT_PREDEF_COMPILER_MPW_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_MPW 0

#if defined(__MRC__) || defined(MPW_C) || defined(MPW_CPLUS)
#	if !defined(SPROUT_COMP_MPW_DETECTION) && defined(__MRC__)
#		define SPROUT_COMP_MPW_DETECTION SPROUT_PREDEF_MAKE_0X_VVRR(__MRC__)
#	endif
#	if !defined(SPROUT_COMP_MPW_DETECTION)
#		define SPROUT_COMP_MPW_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_MPW_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_MPW_EMULATED SPROUT_COMP_MPW_DETECTION
#	else
#		undef SPROUT_COMP_MPW
#		define SPROUT_COMP_MPW SPROUT_COMP_MPW_DETECTION
#	endif
#	define SPROUT_COMP_MPW_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_MPW_NAME "MPW C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_MPW_HPP
