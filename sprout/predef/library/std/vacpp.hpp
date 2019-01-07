/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_VACPP_HPP
#define SPROUT_PREDEF_LIBRARY_STD_VACPP_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>

#define SPROUT_LIB_STD_IBM 0

#if defined(__IBMCPP__)
#	undef SPROUT_LIB_STD_IBM
#	define SPROUT_LIB_STD_IBM 1
#endif

#if SPROUT_LIB_STD_IBM
#	define SPROUT_LIB_STD_IBM_AVAILABLE
#endif

#define SPROUT_LIB_STD_IBM_NAME "IBM VACPP"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_VACPP_HPP
