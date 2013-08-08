/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_ASSERT_HPP
#define TESTSPR_ASSERT_HPP

#include <cassert>
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	include <boost/serialization/static_warning.hpp>
#endif

//
// TESTSPR_STATIC_ASSERT
// TESTSPR_ASSERT
// TESTSPR_BOTH_ASSERT
//
#define TESTSPR_STATIC_ASSERT(expr) static_assert(expr, #expr)
#define TESTSPR_ASSERT(expr) assert(expr)
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_STATIC_ASSERT(expr); TESTSPR_ASSERT(expr)
#else	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_ASSERT(expr)
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

//
// TESTSPR_STATIC_WARNING
//
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	define TESTSPR_STATIC_WARNING(expr) BOOST_STATIC_WARNING(expr)
#else
#	define TESTSPR_STATIC_WARNING(expr)
#endif

//
// TESTSPR_STATIC_UNCHECKED
// TESTSPR_UNCHECKED
// TESTSPR_BOTH_UNCHECKED
//
#define TESTSPR_STATIC_UNCHECKED(expr) TESTSPR_STATIC_WARNING(expr)
#define TESTSPR_UNCHECKED(expr) (expr)
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_UNCHECKED(expr) TESTSPR_STATIC_UNCHECKED(expr); TESTSPR_UNCHECKED(expr)
#else	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_UNCHECKED(expr) TESTSPR_UNCHECKED(expr)
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

#endif	// #ifndef TESTSPR_ASSERT_HPP
