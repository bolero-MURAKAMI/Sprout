/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_STDLIB_LIBCPP_HPP
#define SPROUT_CONFIG_STDLIB_LIBCPP_HPP

#ifdef _LIBCPP_HAS_NO_VARIADICS
#	define SPROUT_NO_CXX11_HDR_TUPLE
#endif

#if defined(_LIBCPP_HAS_NO_TEMPLATE_ALIASES)
#	define SPROUT_NO_CXX11_ALLOCATOR
#	define SPROUT_NO_CXX11_POINTER_TRAITS
#endif

#if __cplusplus < 201103
#	define SPROUT_NO_CXX11_HDR_CODECVT
#	define SPROUT_NO_CXX11_HDR_CONDITION_VARIABLE
#	define SPROUT_NO_CXX11_HDR_INITIALIZER_LIST
#	define SPROUT_NO_CXX11_HDR_MUTEX
#	define SPROUT_NO_CXX11_HDR_RANDOM
#	define SPROUT_NO_CXX11_HDR_RATIO
#	define SPROUT_NO_CXX11_HDR_REGEX
#	define SPROUT_NO_CXX11_HDR_SYSTEM_ERROR
#	define SPROUT_NO_CXX11_HDR_THREAD
#	define SPROUT_NO_CXX11_HDR_TUPLE
#	define SPROUT_NO_CXX11_HDR_TYPEINDEX
#	define SPROUT_NO_CXX11_HDR_UNORDERED_MAP
#	define SPROUT_NO_CXX11_HDR_UNORDERED_SET
#	define SPROUT_NO_CXX11_NUMERIC_LIMITS
#	define SPROUT_NO_CXX11_ALLOCATOR
#	define SPROUT_NO_CXX11_POINTER_TRAITS
#	define SPROUT_NO_CXX11_SMART_PTR
#	define SPROUT_NO_CXX11_HDR_FUNCTIONAL
#	define SPROUT_NO_CXX11_STD_ALIGN
#	define SPROUT_NO_CXX11_ADDRESSOF
#	define SPROUT_NO_CXX11_HDR_ATOMIC
#	define SPROUT_NO_CXX11_ATOMIC_SMART_PTR
#	define SPROUT_NO_CXX11_HDR_CHRONO
#	define SPROUT_NO_CXX11_HDR_TYPE_TRAITS
#	define SPROUT_NO_CXX11_HDR_FUTURE
#elif _LIBCPP_VERSION < 3700
#	define SPROUT_NO_CXX11_HDR_ATOMIC
#	define SPROUT_NO_CXX11_ATOMIC_SMART_PTR
#	define SPROUT_NO_CXX11_HDR_CHRONO
#	define SPROUT_NO_CXX11_HDR_TYPE_TRAITS
#	define SPROUT_NO_CXX11_HDR_FUTURE
#endif

#if _LIBCPP_VERSION < 3700
#	define SPROUT_NO_STD_MESSAGES
#endif

#if (_LIBCPP_VERSION < 3700) || (__cplusplus <= 201402L)
#	define SPROUT_NO_CXX14_STD_EXCHANGE
#endif

#if (_LIBCPP_VERSION < 3700) || (__cplusplus <= 201402L)
#	define SPROUT_NO_CXX17_STD_INVOKE
#endif
#if (_LIBCPP_VERSION < 4000) || (__cplusplus <= 201402L)
#	define SPROUT_NO_CXX17_STD_APPLY
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR)
#	define SPROUT_NO_AUTO_PTR
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_RANDOM_SHUFFLE)
#	define SPROUT_NO_CXX98_RANDOM_SHUFFLE
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_BINDERS)
#	define SPROUT_NO_CXX98_BINDERS
#endif

#if (_LIBCPP_VERSION <= 1101) && !defined(SPROUT_NO_CXX11_THREAD_LOCAL)
#	define SPROUT_NO_CXX11_THREAD_LOCAL
#endif

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#	define SPROUT_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus <= 201103
#	define SPROUT_NO_CXX14_HDR_SHARED_MUTEX
#endif
#elif __cplusplus < 201402
#	define SPROUT_NO_CXX14_HDR_SHARED_MUTEX
#endif

#include <utility>
#if defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION <= 1001)
#	define SPROUT_NO_CXX11_CHAR_TRAITS
#	define SPROUT_NO_CXX11_NUMERIC_LIMITS
#endif

#define SPROUT_NO_CXX14_INITIALIZER_LIST

#endif	// #ifndef SPROUT_CONFIG_STDLIB_LIBCPP_HPP
