/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_CXX_HPP
#define SPROUT_PREDEF_LIBRARY_STD_CXX_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_CXX 0

#if defined(_LIBCPP_VERSION)
#	undef SPROUT_LIB_STD_CXX
#	define SPROUT_LIB_STD_CXX SPROUT_PREDEF_MAKE_10_VPPP(_LIBCPP_VERSION)
#endif

#if SPROUT_LIB_STD_CXX
#	define SPROUT_LIB_STD_CXX_AVAILABLE
#endif

#define SPROUT_LIB_STD_CXX_NAME "libc++"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_CXX_HPP
