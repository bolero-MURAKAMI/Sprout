/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_STDLIB_LIBCPP_HPP
#define SPROUT_CONFIG_STDLIB_LIBCPP_HPP

#ifdef _LIBCPP_HAS_NO_VARIADICS
#	define SPROUT_NO_CXX11_HDR_TUPLE
#endif

#define SPROUT_NO_CXX11_HDR_CHRONO
#define SPROUT_NO_CXX11_HDR_FUTURE
#define SPROUT_NO_CXX11_HDR_TYPE_TRAITS
#define SPROUT_NO_CXX11_ATOMIC_SMART_PTR
#define SPROUT_NO_CXX11_HDR_ATOMIC

#include <utility>
#if defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION <= 1001)
#	define SPROUT_NO_CXX11_CHAR_TRAITS
#	define SPROUT_NO_CXX11_NUMERIC_LIMITS
#endif

#define SPROUT_NO_CXX14_INITIALIZER_LIST

#endif	// #ifndef SPROUT_CONFIG_STDLIB_LIBCPP_HPP
