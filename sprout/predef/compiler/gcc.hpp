/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_GCC_HPP
#define SPROUT_PREDEF_COMPILER_GCC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/compiler/clang.hpp>

#define SPROUT_COMP_GNUC 0

#if defined(__GNUC__)
#	if !defined(SPROUT_COMP_GNUC_DETECTION) && defined(__GNUC_PATCHLEVEL__)
#		define SPROUT_COMP_GNUC_DETECTION \
			SPROUT_VERSION_NUMBER(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#	endif
#	if !defined(SPROUT_COMP_GNUC_DETECTION)
#		define SPROUT_COMP_GNUC_DETECTION \
			SPROUT_VERSION_NUMBER(__GNUC__, __GNUC_MINOR__, 0)
#	endif
#endif

#ifdef SPROUT_COMP_GNUC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_GNUC_EMULATED SPROUT_COMP_GNUC_DETECTION
#	else
#		undef SPROUT_COMP_GNUC
#		define SPROUT_COMP_GNUC SPROUT_COMP_GNUC_DETECTION
#	endif
#	define SPROUT_COMP_GNUC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_GNUC_NAME "Gnu GCC C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_GCC_HPP
