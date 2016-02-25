/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_C_ZOS_HPP
#define SPROUT_PREDEF_LIBRARY_C_ZOS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/c/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_C_ZOS 0

#if defined(__LIBREL__)
#	undef SPROUT_LIB_C_ZOS
#	if !defined(SPROUT_LIB_C_ZOS) && defined(__LIBREL__)
#		define SPROUT_LIB_C_ZOS SPROUT_PREDEF_MAKE_0X_VRRPPPP(__LIBREL__)
#	endif
#	if !defined(SPROUT_LIB_C_ZOS) && defined(__TARGET_LIB__)
#		define SPROUT_LIB_C_ZOS SPROUT_PREDEF_MAKE_0X_VRRPPPP(__TARGET_LIB__)
#	endif
#	if !defined(SPROUT_LIB_C_ZOS)
#		define SPROUT_LIB_C_ZOS 1
#	endif
#endif

#if SPROUT_LIB_C_ZOS
#	define SPROUT_LIB_C_ZOS_AVAILABLE
#endif

#define SPROUT_LIB_C_ZOS_NAME "z/OS"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_C_ZOS_HPP
