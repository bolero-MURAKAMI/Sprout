/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_SGI_HPP
#define SPROUT_PREDEF_LIBRARY_STD_SGI_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_SGI 0

#if defined(__STL_CONFIG_H)
#	undef SPROUT_LIB_STD_SGI
#	if defined(__SGI_STL)
#		define SPROUT_LIB_STD_SGI SPROUT_PREDEF_MAKE_0X_VRP(__SGI_STL)
#	else
#		define SPROUT_LIB_STD_SGI 1
#	endif
#endif

#if SPROUT_LIB_STD_SGI
#	define SPROUT_LIB_STD_SGI_AVAILABLE
#endif

#define SPROUT_LIB_STD_SGI_NAME "SGI"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_SGI_HPP
