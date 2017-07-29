/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_NOT_EQUAL_TO_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_NOT_EQUAL_TO_HPP

#include <sprout/config.hpp>
#include <sprout/functional/not_equal_to.hpp>

namespace sprout {
	//
	// not_equal_to_t
	// not_equal_to_
	//
	typedef sprout::not_equal_to<> not_equal_to_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::not_equal_to_t not_equal_to_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_NOT_EQUAL_TO_HPP
