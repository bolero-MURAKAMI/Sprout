/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_C_GNU_HPP
#define SPROUT_PREDEF_LIBRARY_C_GNU_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/library/c/prefix.hpp>

#if defined(__STDC__)
#	include <stddef.h>
#elif defined(__cplusplus)
#	include <cstddef>
#endif

#define SPROUT_LIB_C_GNU 0

#if defined(__GLIBC__) || defined(__GNU_LIBRARY__)
#	undef SPROUT_LIB_C_GNU
#	if defined(__GLIBC__)
#		define SPROUT_LIB_C_GNU \
			SPROUT_VERSION_NUMBER(__GLIBC__, __GLIBC_MINOR__, 0)
#	else
#		define SPROUT_LIB_C_GNU \
			SPROUT_VERSION_NUMBER(__GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0)
#	endif
#endif

#if SPROUT_LIB_C_GNU
#	define SPROUT_LIB_C_GNU_AVAILABLE
#endif

#define SPROUT_LIB_C_GNU_NAME "GNU"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_C_GNU_HPP
