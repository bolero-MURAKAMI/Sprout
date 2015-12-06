/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_METROWERKS_HPP
#define SPROUT_PREDEF_COMPILER_METROWERKS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_MWERKS 0

#if defined(__MWERKS__) || defined(__CWCC__)
#	if !defined(SPROUT_COMP_MWERKS_DETECTION) && defined(__CWCC__)
#		define SPROUT_COMP_MWERKS_DETECTION SPROUT_PREDEF_MAKE_0X_VRPP(__CWCC__)
#	endif
#	if !defined(SPROUT_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x4200)
#		define SPROUT_COMP_MWERKS_DETECTION SPROUT_PREDEF_MAKE_0X_VRPP(__MWERKS__)
#	endif
#	if !defined(SPROUT_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3204)
#		define SPROUT_COMP_MWERKS_DETECTION SPROUT_VERSION_NUMBER(9, (__MWERKS__) % 100 - 1, 0)
#	endif
#	if !defined(SPROUT_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3200)
#		define SPROUT_COMP_MWERKS_DETECTION SPROUT_VERSION_NUMBER(9, (__MWERKS__) % 100, 0)
#	endif
#	if !defined(SPROUT_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3000)
#		define SPROUT_COMP_MWERKS_DETECTION SPROUT_VERSION_NUMBER(8, (__MWERKS__) % 100, 0)
#	endif
#	if !defined(SPROUT_COMP_MWERKS_DETECTION)
#		define SPROUT_COMP_MWERKS_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_MWERKS_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_MWERKS_EMULATED SPROUT_COMP_MWERKS_DETECTION
#	else
#		undef SPROUT_COMP_MWERKS
#		define SPROUT_COMP_MWERKS SPROUT_COMP_MWERKS_DETECTION
#	endif
#	define SPROUT_COMP_MWERKS_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_MWERKS_NAME "Metrowerks CodeWarrior"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_METROWERKS_HPP
