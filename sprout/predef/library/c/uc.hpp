/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_C_UC_HPP
#define SPROUT_PREDEF_LIBRARY_C_UC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/c/prefix.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_LIB_C_UC 0

#if defined(__UCLIBC__)
#	undef SPROUT_LIB_C_UC
#	define SPROUT_LIB_C_UC \
		SPROUT_VERSION_NUMBER(__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__)
#endif

#if SPROUT_LIB_C_UC
#	define SPROUT_LIB_C_UC_AVAILABLE
#endif

#define SPROUT_LIB_C_UC_NAME "uClibc"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_C_UC_HPP
