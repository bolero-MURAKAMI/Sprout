/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATIC_ASSERT_HPP
#define SPROUT_STATIC_ASSERT_HPP

#include <sprout/config.hpp>
#include <sprout/preprocessor/stringize.hpp>

//
// SPROUT_STATIC_ASSERT_MSG
// SPROUT_STATIC_ASSERT
// SPROUT_STATIC_ASSERT_PREPROCESSED
//
#define SPROUT_STATIC_ASSERT_MSG(COND, MESSAGE) \
	static_assert(COND, MESSAGE)
#define SPROUT_STATIC_ASSERT(COND) \
	SPROUT_STATIC_ASSERT_MSG(COND, #COND)
#define SPROUT_STATIC_ASSERT_PREPROCESSED(COND) \
	SPROUT_STATIC_ASSERT_MSG(COND, #COND " \n[[preprocessed]]: " SPROUT_PP_STRINGIZE(COND))

#endif	// #ifndef SPROUT_STATIC_ASSERT_HPP
