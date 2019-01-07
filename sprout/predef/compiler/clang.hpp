/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_CLANG_HPP
#define SPROUT_PREDEF_COMPILER_CLANG_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_COMP_CLANG 0

#if defined(__clang__)
#	define SPROUT_COMP_CLANG_DETECTION \
		SPROUT_VERSION_NUMBER(__clang_major__, __clang_minor__, __clang_patchlevel__)
#endif

#ifdef SPROUT_COMP_CLANG_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_CLANG_EMULATED SPROUT_COMP_CLANG_DETECTION
#	else
#		undef SPROUT_COMP_CLANG
#		define SPROUT_COMP_CLANG SPROUT_COMP_CLANG_DETECTION
#	endif
#	define SPROUT_COMP_CLANG_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_CLANG_NAME "Clang"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_CLANG_HPP
