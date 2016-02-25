/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_STDLIB_DINKUMWARE_HPP
#define SPROUT_CONFIG_STDLIB_DINKUMWARE_HPP

#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 520
#	define SPROUT_NO_CXX11_HDR_ARRAY
#	define SPROUT_NO_CXX11_HDR_CODECVT
#	define SPROUT_NO_CXX11_HDR_FORWARD_LIST
#	define SPROUT_NO_CXX11_HDR_INITIALIZER_LIST
#	define SPROUT_NO_CXX11_HDR_RANDOM
#	define SPROUT_NO_CXX11_HDR_REGEX
#	define SPROUT_NO_CXX11_HDR_SYSTEM_ERROR
#	define SPROUT_NO_CXX11_HDR_UNORDERED_MAP
#	define SPROUT_NO_CXX11_HDR_UNORDERED_SET
#	define SPROUT_NO_CXX11_HDR_TUPLE
#	define SPROUT_NO_CXX11_HDR_TYPEINDEX
#	define SPROUT_NO_CXX11_HDR_FUNCTIONAL
#	define SPROUT_NO_CXX11_CHAR_TRAITS
#	define SPROUT_NO_CXX11_NUMERIC_LIMITS
#	define SPROUT_NO_CXX11_SMART_PTR
#endif

#if (!defined(_HAS_TR1_IMPORTS) || (_HAS_TR1_IMPORTS+0 == 0)) && !defined(SPROUT_NO_CXX11_HDR_TUPLE) && (!defined(_CPPLIB_VER) || _CPPLIB_VER < 610)
#	define SPROUT_NO_CXX11_HDR_TUPLE
#endif

#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 540
#	define SPROUT_NO_CXX11_HDR_TYPE_TRAITS
#	define SPROUT_NO_CXX11_HDR_CHRONO
#	define SPROUT_NO_CXX11_HDR_CONDITION_VARIABLE
#	define SPROUT_NO_CXX11_HDR_FUTURE
#	define SPROUT_NO_CXX11_HDR_MUTEX
#	define SPROUT_NO_CXX11_HDR_RATIO
#	define SPROUT_NO_CXX11_HDR_THREAD
#	define SPROUT_NO_CXX11_ALLOCATOR
#	define SPROUT_NO_CXX11_ATOMIC_SMART_PTR
#endif

#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 610
#	define SPROUT_NO_CXX11_HDR_INITIALIZER_LIST
#	define SPROUT_NO_CXX11_HDR_ATOMIC
#endif

#define SPROUT_NO_CXX14_INITIALIZER_LIST

#endif	// #ifndef SPROUT_CONFIG_STDLIB_DINKUMWARE_HPP
