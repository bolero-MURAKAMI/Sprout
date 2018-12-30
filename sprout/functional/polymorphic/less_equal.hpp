/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LESS_EQUAL_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_LESS_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/functional/less_equal.hpp>

namespace sprout {
	//
	// less_equal_t
	// less_equal_
	//
	typedef sprout::less_equal<> less_equal_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::less_equal_t less_equal_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LESS_EQUAL_HPP
