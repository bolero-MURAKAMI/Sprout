/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_ASSERT_HPP
#define TESTSPR_ASSERT_HPP

#include <string>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/assert.hpp>
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	include <sprout/static_warning.hpp>
#endif

namespace testspr {
	//
	// assertion_failed
	//
	class assertion_failed
		: public std::runtime_error
	{
	public:
		explicit SPROUT_NON_CONSTEXPR assertion_failed(std::string const& msg)
			: std::runtime_error(msg)
		{}
		explicit SPROUT_NON_CONSTEXPR assertion_failed(char const* msg)
			: std::runtime_error(msg)
		{}
	};

	namespace detail {
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, std::string const& msg) {
			return cond ? true
				: throw testspr::assertion_failed(msg)
				;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, char const* msg) {
			return cond ? true
				: throw testspr::assertion_failed(msg)
				;
		}
	}	// namespace detail
}	// namespace testspr

//
// TESTSPR_STATIC_ASSERT
// TESTSPR_ASSERT
//
#define TESTSPR_STATIC_ASSERT(expr) \
	static_assert(expr, #expr)
#define TESTSPR_ASSERT(expr) \
	SPROUT_ASSERT(expr)
//
// TESTSPR_BOTH_ASSERT
//
#if !defined(SPROUT_CONFIG_DISABLE_CONSTEXPR) && !defined(SPROUT_NO_STATIC_CONSTEXPR_INITIALIZATION)
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_STATIC_ASSERT(expr); TESTSPR_ASSERT(expr)
#else
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_ASSERT(expr)
#endif

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
