/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_EKOPATH_HPP
#define SPROUT_PREDEF_COMPILER_EKOPATH_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_COMP_PATH 0

#if defined(__PATHCC__)
#	define SPROUT_COMP_PATH_DETECTION \
		SPROUT_VERSION_NUMBER(__PATHCC__, __PATHCC_MINOR__, __PATHCC_PATCHLEVEL__)
#endif

#ifdef SPROUT_COMP_PATH_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_PATH_EMULATED SPROUT_COMP_PATH_DETECTION
#	else
#		undef SPROUT_COMP_PATH
#		define SPROUT_COMP_PATH SPROUT_COMP_PATH_DETECTION
#	endif
#	define SPROUT_COMP_PATH_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_PATH_NAME "EKOpath"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_EKOPATH_HPP
