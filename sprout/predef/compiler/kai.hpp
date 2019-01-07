/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_KAI_HPP
#define SPROUT_PREDEF_COMPILER_KAI_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_KCC 0

#if defined(__KCC)
#	define SPROUT_COMP_KCC_DETECTION SPROUT_PREDEF_MAKE_0X_VRPP(__KCC_VERSION)
#endif

#ifdef SPROUT_COMP_KCC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_KCC_EMULATED SPROUT_COMP_KCC_DETECTION
#	else
#		undef SPROUT_COMP_KCC
#		define SPROUT_COMP_KCC SPROUT_COMP_KCC_DETECTION
#	endif
#	define SPROUT_COMP_KCC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_KCC_NAME "Kai C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_KAI_HPP
