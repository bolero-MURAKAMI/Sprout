/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_METAWARE_HPP
#define SPROUT_PREDEF_COMPILER_METAWARE_HPP

#include <sprout/config.hpp>

#define SPROUT_COMP_HIGHC 0

#if defined(__HIGHC__)
#	define SPROUT_COMP_HIGHC_DETECTION 1
#endif

#ifdef SPROUT_COMP_HIGHC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_HIGHC_EMULATED SPROUT_COMP_HIGHC_DETECTION
#	else
#		undef SPROUT_COMP_HIGHC
#		define SPROUT_COMP_HIGHC SPROUT_COMP_HIGHC_DETECTION
#	endif
#	define SPROUT_COMP_HIGHC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_HIGHC_NAME "MetaWare High C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_METAWARE_HPP
