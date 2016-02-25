/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATIC_ASSERT_HPP
#define SPROUT_STATIC_ASSERT_HPP

#include <sprout/config.hpp>
#include <sprout/preprocessor/config.hpp>
#include <sprout/preprocessor/stringize.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/preprocessor/variadic/size.hpp>

//
// SPROUT_STATIC_ASSERT_MSG
//
#define SPROUT_STATIC_ASSERT_MSG(COND, MESSAGE) \
	static_assert(COND, MESSAGE)

//
// SPROUT_STATIC_ASSERT
//
#define SPROUT_STATIC_ASSERT_1(COND) \
	SPROUT_STATIC_ASSERT_MSG(COND, #COND)
#if SPROUT_PP_VARIADICS
#	define SPROUT_STATIC_ASSERT_2(COND, MESSAGE) \
		SPROUT_STATIC_ASSERT_MSG(COND, MESSAGE)
#	define SPROUT_STATIC_ASSERT(...) \
		SPROUT_PP_CAT(SPROUT_STATIC_ASSERT_, SPROUT_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)
#else
#	define SPROUT_STATIC_ASSERT(COND) \
		SPROUT_STATIC_ASSERT_1(COND)
#endif

//
// SPROUT_STATIC_ASSERT_PREPROCESSED
//
#define SPROUT_STATIC_ASSERT_PREPROCESSED(COND) \
	SPROUT_STATIC_ASSERT_MSG(COND, #COND " \n[[preprocessed]] " SPROUT_PP_STRINGIZE(COND))

#endif	// #ifndef SPROUT_STATIC_ASSERT_HPP
