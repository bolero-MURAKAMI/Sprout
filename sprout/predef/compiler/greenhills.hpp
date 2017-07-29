/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_GREENHILLS_HPP
#define SPROUT_PREDEF_COMPILER_GREENHILLS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_GHS 0

#if defined(__ghs) || defined(__ghs__)
#	if !defined(SPROUT_COMP_GHS_DETECTION) && defined(__GHS_VERSION_NUMBER__)
#		define SPROUT_COMP_GHS_DETECTION SPROUT_PREDEF_MAKE_10_VRP(__GHS_VERSION_NUMBER__)
#	endif
#	if !defined(SPROUT_COMP_GHS_DETECTION) && defined(__ghs)
#		define SPROUT_COMP_GHS_DETECTION SPROUT_PREDEF_MAKE_10_VRP(__ghs)
#	endif
#	if !defined(SPROUT_COMP_GHS_DETECTION)
#		define SPROUT_COMP_GHS_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_GHS_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_GHS_EMULATED SPROUT_COMP_GHS_DETECTION
#	else
#		undef SPROUT_COMP_GHS
#		define SPROUT_COMP_GHS SPROUT_COMP_GHS_DETECTION
#	endif
#	define SPROUT_COMP_GHS_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_GHS_NAME "Green Hills C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_GREENHILLS_HPP
