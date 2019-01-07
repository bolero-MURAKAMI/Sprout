/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_IBM_HPP
#define SPROUT_PREDEF_COMPILER_IBM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_IBM 0

#if defined(__IBMCPP__) || defined(__xlC__) || defined(__xlc__)
#	if !defined(SPROUT_COMP_IBM_DETECTION) && defined(__COMPILER_VER__)
#		define SPROUT_COMP_IBM_DETECTION SPROUT_PREDEF_MAKE_0X_VRRPPPP(__COMPILER_VER__)
#	endif
#	if !defined(SPROUT_COMP_IBM_DETECTION) && defined(__xlC__)
#		define SPROUT_COMP_IBM_DETECTION SPROUT_PREDEF_MAKE_0X_VVRR(__xlC__)
#	endif
#	if !defined(SPROUT_COMP_IBM_DETECTION) && defined(__xlc__)
#		define SPROUT_COMP_IBM_DETECTION SPROUT_PREDEF_MAKE_0X_VVRR(__xlc__)
#	endif
#	if !defined(SPROUT_COMP_IBM_DETECTION)
#		define SPROUT_COMP_IBM_DETECTION SPROUT_PREDEF_MAKE_10_VRP(__IBMCPP__)
#	endif
#endif

#ifdef SPROUT_COMP_IBM_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_IBM_EMULATED SPROUT_COMP_IBM_DETECTION
#	else
#		undef SPROUT_COMP_IBM
#		define SPROUT_COMP_IBM SPROUT_COMP_IBM_DETECTION
#	endif
#	define SPROUT_COMP_IBM_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_IBM_NAME "IBM XL C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_IBM_HPP
