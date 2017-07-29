/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_GREATER_EQUAL_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_GREATER_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/functional/greater_equal.hpp>

namespace sprout {
	//
	// greater_equal_t
	// greater_equal_
	//
	typedef sprout::greater_equal<> greater_equal_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::greater_equal_t greater_equal_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_GREATER_EQUAL_HPP
