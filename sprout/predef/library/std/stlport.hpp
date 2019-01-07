/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_STLPORT_HPP
#define SPROUT_PREDEF_LIBRARY_STD_STLPORT_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_STLPORT 0

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#	undef SPROUT_LIB_STD_STLPORT
#	if !defined(SPROUT_LIB_STD_STLPORT) && defined(_STLPORT_MAJOR)
#		define SPROUT_LIB_STD_STLPORT \
			SPROUT_VERSION_NUMBER(_STLPORT_MAJOR, _STLPORT_MINOR, _STLPORT_PATCHLEVEL)
#	endif
#	if !defined(SPROUT_LIB_STD_STLPORT) && defined(_STLPORT_VERSION)
#		define SPROUT_LIB_STD_STLPORT SPROUT_PREDEF_MAKE_0X_VRP(_STLPORT_VERSION)
#	endif
#	if !defined(SPROUT_LIB_STD_STLPORT)
#		define SPROUT_LIB_STD_STLPORT SPROUT_PREDEF_MAKE_0X_VRP(__SGI_STL_PORT)
#	endif
#endif

#if SPROUT_LIB_STD_STLPORT
#	define SPROUT_LIB_STD_STLPORT_AVAILABLE
#endif

#define SPROUT_LIB_STD_STLPORT_NAME "STLport"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_STLPORT_HPP
