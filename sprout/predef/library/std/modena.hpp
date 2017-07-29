/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_MODENA_HPP
#define SPROUT_PREDEF_LIBRARY_STD_MODENA_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>

#define SPROUT_LIB_STD_MSIPL 0

#if defined(MSIPL_COMPILE_H) || defined(__MSIPL_COMPILE_H)
#	undef SPROUT_LIB_STD_MSIPL
#	define SPROUT_LIB_STD_MSIPL 1
#endif

#if SPROUT_LIB_STD_MSIPL
#	define SPROUT_LIB_STD_MSIPL_AVAILABLE
#endif

#define SPROUT_LIB_STD_MSIPL_NAME "Modena Software Lib++"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_MODENA_HPP
