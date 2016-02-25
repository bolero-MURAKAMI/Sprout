/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_PREDEF_HPP
#define SPROUT_DETAIL_PREDEF_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

//
// SPROUT_AVAILABLE_GCC
//
#if defined(__GNUC__)
#	define SPROUT_AVAILABLE_GCC (1)
#else
#	define SPROUT_AVAILABLE_GCC (0)
#endif
//
// SPROUT_VERSION_GCC
//
#if SPROUT_AVAILABLE_GCC
#	define SPROUT_VERSION_GCC SPROUT_VERSION_NUMBER(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
#	define SPROUT_VERSION_GCC SPROUT_VERSION_NUMBER_ZERO
#endif
//
// SPROUT_GCC_EARLIER
// SPROUT_GCC_OR_LATER
//
#if SPROUT_AVAILABLE_GCC
#	define SPROUT_GCC_EARLIER(MAJOR, MINOR, PATCH) \
		(SPROUT_VERSION_GCC < SPROUT_VERSION_NUMBER(MAJOR, MINOR, PATCH))
#	define SPROUT_GCC_OR_LATER(MAJOR, MINOR, PATCH) \
		(SPROUT_VERSION_GCC >= SPROUT_VERSION_NUMBER(MAJOR, MINOR, PATCH))
#else
#	define SPROUT_GCC_EARLIER(MAJOR, MINOR, PATCH) \
		(0)
#	define SPROUT_GCC_OR_LATER(MAJOR, MINOR, PATCH) \
		(0)
#endif
//
// SPROUT_GCC_IN_RANGE
//
#if SPROUT_AVAILABLE_GCC
#	define SPROUT_GCC_IN_RANGE(first_version, last_version) \
		(SPROUT_GCC_OR_LATER first_version && SPROUT_GCC_EARLIER last_version)
#else
#	define SPROUT_GCC_IN_RANGE(first_version, last_version) \
		(0)
#endif

//
// SPROUT_AVAILABLE_CLANG
//
#if defined(__clang__)
#	define SPROUT_AVAILABLE_CLANG (1)
#else
#	define SPROUT_AVAILABLE_CLANG (0)
#endif
//
// SPROUT_VERSION_CLANG
//
#if SPROUT_AVAILABLE_CLANG
#	define SPROUT_VERSION_CLANG SPROUT_VERSION_NUMBER(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
#	define SPROUT_VERSION_CLANG SPROUT_VERSION_NUMBER_ZERO
#endif
//
// SPROUT_CLANG_HAS_FUTURE
//
#if SPROUT_AVAILABLE_CLANG
#	define SPROUT_CLANG_HAS_FUTURE(future) (__has_feature(future))
#else
#	define SPROUT_CLANG_HAS_FUTURE(future) (0)
#endif
//
// SPROUT_CLANG_EARLIER
// SPROUT_CLANG_OR_LATER
//
#if SPROUT_AVAILABLE_CLANG
#	define SPROUT_CLANG_EARLIER(MAJOR, MINOR, PATCH) \
		(SPROUT_VERSION_CLANG < SPROUT_VERSION_NUMBER(MAJOR, MINOR, PATCH))
#	define SPROUT_CLANG_OR_LATER(MAJOR, MINOR, PATCH) \
		(SPROUT_VERSION_CLANG >= SPROUT_VERSION_NUMBER(MAJOR, MINOR, PATCH))
#else
#	define SPROUT_CLANG_EARLIER(MAJOR, MINOR, PATCH) \
		(0)
#	define SPROUT_CLANG_OR_LATER(MAJOR, MINOR, PATCH) \
		(0)
#endif
//
// SPROUT_CLANG_IN_RANGE
//
#if SPROUT_AVAILABLE_CLANG
#	define SPROUT_CLANG_IN_RANGE(first_version, last_version) \
		(SPROUT_CLANG_OR_LATER first_version && SPROUT_CLANG_EARLIER last_version)
#else
#	define SPROUT_CLANG_IN_RANGE(first_version, last_version) \
		(0)
#endif

#endif	// #ifndef SPROUT_DETAIL_PREDEF_HPP
