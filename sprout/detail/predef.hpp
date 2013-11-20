/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_PREDEF_HPP
#define SPROUT_DETAIL_PREDEF_HPP

#include <sprout/config.hpp>

//
// SPROUT_IS_GCC
//
#if defined(__GNUC__)
#	define SPROUT_IS_GCC (1)
#else
#	define SPROUT_IS_GCC (0)
#endif
//
// SPROUT_GCC_LESS
// SPROUT_GCC_GREATER
// SPROUT_GCC_LESS_EQUAL
// SPROUT_GCC_GREATER_EQUAL
//
#if SPROUT_IS_GCC
#	define SPROUT_GCC_LESS(major, minor, patch) ( \
		__GNUC__ < major \
		|| (__GNUC__ == major && __GNUC_MINOR__ < minor) \
		|| (__GNUC__ == major && __GNUC_MINOR__ == minor && __GNUC_PATCHLEVEL__ < patch) \
		)
#	define SPROUT_GCC_GREATER(major, minor, patch) ( \
		__GNUC__ > major \
		|| (__GNUC__ == major && __GNUC_MINOR__ > minor) \
		|| (__GNUC__ == major && __GNUC_MINOR__ == minor && __GNUC_PATCHLEVEL__ > patch) \
		)
#	define SPROUT_GCC_LESS_EQUAL(major, minor, patch) ( \
		__GNUC__ < major \
		|| (__GNUC__ == major && __GNUC_MINOR__ < minor) \
		|| (__GNUC__ == major && __GNUC_MINOR__ == minor && __GNUC_PATCHLEVEL__ <= patch) \
		)
#	define SPROUT_GCC_GREATER_EQUAL(major, minor, patch) ( \
		__GNUC__ > major \
		|| (__GNUC__ == major && __GNUC_MINOR__ > minor) \
		|| (__GNUC__ == major && __GNUC_MINOR__ == minor && __GNUC_PATCHLEVEL__ >= patch) \
		)
#else
#	define SPROUT_GCC_LESS(major, minor, patch) (0)
#	define SPROUT_GCC_GREATER(major, minor, patch) (0)
#	define SPROUT_GCC_LESS_EQUAL(major, minor, patch) (0)
#	define SPROUT_GCC_GREATER_EQUAL(major, minor, patch) (0)
#endif
//
// SPROUT_GCC_BETWEEN
//
#if SPROUT_IS_GCC
#	define SPROUT_GCC_BETWEEN(major1, minor1, patch1, major2, minor2, patch2) \
		SPROUT_GCC_GREATER_EQUAL(major1, minor1, patch1) && SPROUT_GCC_LESS(major2, minor2, patch2)
#else
#	define SPROUT_GCC_BETWEEN(major1, minor1, patch1, major2, minor2, patch2) (0)
#endif

//
// SPROUT_IS_CLANG
//
#if defined(__clang__)
#	define SPROUT_IS_CLANG (1)
#else
#	define SPROUT_IS_CLANG (0)
#endif
//
// SPROUT_CLANG_HAS_FUTURE
//
#if SPROUT_IS_CLANG
#	define SPROUT_CLANG_HAS_FUTURE(future) (__has_feature(future))
#else
#	define SPROUT_CLANG_HAS_FUTURE(future) (0)
#endif
//
// SPROUT_CLANG_LESS
// SPROUT_CLANG_GREATER
// SPROUT_CLANG_LESS_EQUAL
// SPROUT_CLANG_GREATER_EQUAL
//
#if SPROUT_IS_CLANG
#	define SPROUT_CLANG_LESS(major, minor, patch) ( \
		__clang_major__ < major \
		|| (__clang_major__ == major && __clang_minor__ < minor) \
		|| (__clang_major__ == major && __clang_minor__ == minor && __clang_patchlevel__ < patch) \
		)
#	define SPROUT_CLANG_GREATER(major, minor, patch) ( \
		__clang_major__ > major \
		|| (__clang_major__ == major && __clang_minor__ > minor) \
		|| (__clang_major__ == major && __clang_minor__ == minor && __clang_patchlevel__ > patch) \
		)
#	define SPROUT_CLANG_LESS_EQUAL(major, minor, patch) ( \
		__clang_major__ < major \
		|| (__clang_major__ == major && __clang_minor__ < minor) \
		|| (__clang_major__ == major && __clang_minor__ == minor && __clang_patchlevel__ <= patch) \
		)
#	define SPROUT_CLANG_GREATER_EQUAL(major, minor, patch) ( \
		__clang_major__ > major \
		|| (__clang_major__ == major && __clang_minor__ > minor) \
		|| (__clang_major__ == major && __clang_minor__ == minor && __clang_patchlevel__ >= patch) \
		)
#else
#	define SPROUT_CLANG_LESS(major, minor, patch) (0)
#	define SPROUT_CLANG_GREATER(major, minor, patch) (0)
#	define SPROUT_CLANG_LESS_EQUAL(major, minor, patch) (0)
#	define SPROUT_CLANG_GREATER_EQUAL(major, minor, patch) (0)
#endif
//
// SPROUT_CLANG_BETWEEN
//
#if SPROUT_IS_CLANG
#	define SPROUT_CLANG_BETWEEN(major1, minor1, patch1, major2, minor2, patch2) \
		SPROUT_CLANG_GREATER_EQUAL(major1, minor1, patch1) && SPROUT_CLANG_LESS(major2, minor2, patch2)
#else
#	define SPROUT_CLANG_BETWEEN(major1, minor1, patch1, major2, minor2, patch2) (0)
#endif

#endif	// #ifndef SPROUT_DETAIL_PREDEF_HPP
