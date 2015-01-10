/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_STDLIB_LIBSTDCPP3_HPP
#define SPROUT_CONFIG_STDLIB_LIBSTDCPP3_HPP

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 3) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_NO_CXX11_HDR_ARRAY
#	define SPROUT_NO_CXX11_HDR_REGEX
#	define SPROUT_NO_CXX11_HDR_TUPLE
#	define SPROUT_NO_CXX11_HDR_UNORDERED_MAP
#	define SPROUT_NO_CXX11_HDR_UNORDERED_SET
#	define SPROUT_NO_CXX11_HDR_FUNCTIONAL
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_NO_CXX11_HDR_CONDITION_VARIABLE
#	define SPROUT_NO_CXX11_HDR_FORWARD_LIST
#	define SPROUT_NO_CXX11_HDR_INITIALIZER_LIST
#	define SPROUT_NO_CXX11_HDR_MUTEX
#	define SPROUT_NO_CXX11_HDR_RATIO
#	define SPROUT_NO_CXX11_HDR_SYSTEM_ERROR
#	define SPROUT_NO_CXX11_SMART_PTR
#endif

#if (!defined(_GLIBCXX_HAS_GTHREADS) || !defined(_GLIBCXX_USE_C99_STDINT_TR1)) && (!defined(SPROUT_NO_CXX11_HDR_CONDITION_VARIABLE) || !defined(SPROUT_NO_CXX11_HDR_MUTEX))
#	define SPROUT_NO_CXX11_HDR_CONDITION_VARIABLE
#	define SPROUT_NO_CXX11_HDR_MUTEX
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	if defined(__clang__)
#		if !__has_feature(cxx_constexpr) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#			define SPROUT_NO_CXX11_CHAR_TRAITS
#			define SPROUT_NO_CXX11_NUMERIC_LIMITS
#		endif
#	else
#		define SPROUT_NO_CXX11_CHAR_TRAITS
#		define SPROUT_NO_CXX11_NUMERIC_LIMITS
#	endif
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_NO_CXX11_HDR_FUTURE
#	define SPROUT_NO_CXX11_HDR_RANDOM
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_NO_CXX11_HDR_TYPEINDEX
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#	define SPROUT_NO_CXX11_HDR_CHRONO
#	define SPROUT_NO_CXX11_ALLOCATOR
#endif

#define SPROUT_NO_CXX11_HDR_THREAD
#define SPROUT_NO_CXX11_HDR_TYPE_TRAITS
#define SPROUT_NO_CXX11_HDR_CODECVT
#define SPROUT_NO_CXX11_ATOMIC_SMART_PTR

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_CXX14_INITIALIZER_LIST
#endif

#endif	// #ifndef SPROUT_CONFIG_STDLIB_LIBSTDCPP3_HPP
