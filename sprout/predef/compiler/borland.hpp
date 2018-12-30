/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_BORLAND_HPP
#define SPROUT_PREDEF_COMPILER_BORLAND_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_BORLAND 0

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#	if !defined(SPROUT_COMP_BORLAND_DETECTION) && (defined(__CODEGEARC__))
#		define SPROUT_COMP_BORLAND_DETECTION SPROUT_PREDEF_MAKE_0X_VVRP(__CODEGEARC__)
#	endif
#	if !defined(SPROUT_COMP_BORLAND_DETECTION)
#		define SPROUT_COMP_BORLAND_DETECTION SPROUT_PREDEF_MAKE_0X_VVRP(__BORLANDC__)
#	endif
#endif

#ifdef SPROUT_COMP_BORLAND_DETECTION
#	define SPROUT_COMP_BORLAND_AVAILABLE
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_BORLAND_EMULATED SPROUT_COMP_BORLAND_DETECTION
#	else
#		undef SPROUT_COMP_BORLAND
#		define SPROUT_COMP_BORLAND SPROUT_COMP_BORLAND_DETECTION
#	endif
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_BORLAND_NAME "Borland C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_BORLAND_HPP
