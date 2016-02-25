/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_C_VMS_HPP
#define SPROUT_PREDEF_LIBRARY_C_VMS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/c/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_C_VMS 0

#if defined(__CRTL_VER)
#	undef SPROUT_LIB_C_VMS
#	define SPROUT_LIB_C_VMS SPROUT_PREDEF_MAKE_10_VVRR0PP00(__CRTL_VER)
#endif

#if SPROUT_LIB_C_VMS
#	define SPROUT_LIB_C_VMS_AVAILABLE
#endif

#define SPROUT_LIB_C_VMS_NAME "VMS"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_C_VMS_HPP
