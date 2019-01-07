/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_VISUALC_HPP
#define SPROUT_PREDEF_COMPILER_VISUALC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/compiler/clang.hpp>

#define SPROUT_COMP_MSVC 0

#if defined(_MSC_VER)
#	if !defined (_MSC_FULL_VER)
#		define SPROUT_COMP_MSVC_BUILD 0
#	else
#		if _MSC_FULL_VER / 10000 == _MSC_VER
#			define SPROUT_COMP_MSVC_BUILD (_MSC_FULL_VER % 10000)
#		elif _MSC_FULL_VER / 100000 == _MSC_VER
#			define SPROUT_COMP_MSVC_BUILD (_MSC_FULL_VER % 100000)
#		else
#			error "Cannot determine build number from _MSC_FULL_VER"
#		endif
#	endif
#	if (_MSC_VER >= 1900)
#		define SPROUT_COMP_MSVC_DETECTION \
			SPROUT_VERSION_NUMBER(_MSC_VER / 100 - 5, _MSC_VER % 100, SPROUT_COMP_MSVC_BUILD)
#	else
#		define SPROUT_COMP_MSVC_DETECTION \
			SPROUT_VERSION_NUMBER(_MSC_VER / 100 - 6, _MSC_VER % 100, SPROUT_COMP_MSVC_BUILD)
#	endif
#endif

#ifdef SPROUT_COMP_MSVC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_MSVC_EMULATED SPROUT_COMP_MSVC_DETECTION
#	else
#		undef SPROUT_COMP_MSVC
#		define SPROUT_COMP_MSVC SPROUT_COMP_MSVC_DETECTION
#	endif
#	define SPROUT_COMP_MSVC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_MSVC_NAME "Microsoft Visual C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_VISUALC_HPP
