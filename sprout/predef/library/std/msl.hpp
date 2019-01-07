/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_MSL_HPP
#define SPROUT_PREDEF_LIBRARY_STD_MSL_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_MSL 0

#if defined(__MSL_CPP__) || defined(__MSL__)
#	undef SPROUT_LIB_STD_MSL
#	if defined(__MSL_CPP__)
#		define SPROUT_LIB_STD_MSL SPROUT_PREDEF_MAKE_0X_VRPP(__MSL_CPP__)
#	else
#		define SPROUT_LIB_STD_MSL SPROUT_PREDEF_MAKE_0X_VRPP(__MSL__)
#	endif
#endif

#if SPROUT_LIB_STD_MSL
#	define SPROUT_LIB_STD_MSL_AVAILABLE
#endif

#define SPROUT_LIB_STD_MSL_NAME "Metrowerks"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_MSL_HPP
