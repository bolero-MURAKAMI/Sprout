/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_LIBCOMO_HPP
#define SPROUT_PREDEF_LIBRARY_STD_LIBCOMO_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_LIB_STD_COMO 0

#if defined(__LIBCOMO__)
#	undef SPROUT_LIB_STD_COMO
#	define SPROUT_LIB_STD_COMO SPROUT_VERSION_NUMBER(__LIBCOMO_VERSION__, 0, 0)
#endif

#if SPROUT_LIB_STD_COMO
#	define SPROUT_LIB_STD_COMO_AVAILABLE
#endif

#define SPROUT_LIB_STD_COMO_NAME "Comeau Computing"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_LIBCOMO_HPP
