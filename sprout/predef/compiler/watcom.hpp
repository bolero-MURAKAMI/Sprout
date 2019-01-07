/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_WATCOM_HPP
#define SPROUT_PREDEF_COMPILER_WATCOM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_WATCOM 0

#if defined(__WATCOMC__)
#	define SPROUT_COMP_WATCOM_DETECTION SPROUT_PREDEF_MAKE_10_VVRR(__WATCOMC__)
#endif

#ifdef SPROUT_COMP_WATCOM_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_WATCOM_EMULATED SPROUT_COMP_WATCOM_DETECTION
#	else
#		undef SPROUT_COMP_WATCOM
#		define SPROUT_COMP_WATCOM SPROUT_COMP_WATCOM_DETECTION
#	endif
#	define SPROUT_COMP_WATCOM_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_WATCOM_NAME "Watcom C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_WATCOM_HPP
