/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_DINKUMWARE_HPP
#define SPROUT_PREDEF_LIBRARY_STD_DINKUMWARE_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_DINKUMWARE 0

#if (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
#	undef SPROUT_LIB_STD_DINKUMWARE
#	if defined(_CPPLIB_VER)
#		define SPROUT_LIB_STD_DINKUMWARE SPROUT_PREDEF_MAKE_10_VVRR(_CPPLIB_VER)
#	else
#		define SPROUT_LIB_STD_DINKUMWARE 1
#	endif
#endif

#if SPROUT_LIB_STD_DINKUMWARE
#	define SPROUT_LIB_STD_DINKUMWARE_AVAILABLE
#endif

#define SPROUT_LIB_STD_DINKUMWARE_NAME "Dinkumware"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_DINKUMWARE_HPP
