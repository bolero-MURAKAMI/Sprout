/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_STDCPP3_HPP
#define SPROUT_PREDEF_LIBRARY_STD_STDCPP3_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_GNU 0

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#	undef SPROUT_LIB_STD_GNU
#	if defined(__GLIBCXX__)
#		define SPROUT_LIB_STD_GNU SPROUT_PREDEF_MAKE_YYYYMMDD(__GLIBCXX__)
#	else
#		define SPROUT_LIB_STD_GNU SPROUT_PREDEF_MAKE_YYYYMMDD(__GLIBCPP__)
#	endif
#endif

#if SPROUT_LIB_STD_GNU
#	define SPROUT_LIB_STD_GNU_AVAILABLE
#endif

#define SPROUT_LIB_STD_GNU_NAME "GNU"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_STDCPP3_HPP
