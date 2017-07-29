/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_EQUAL_TO_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_EQUAL_TO_HPP

#include <sprout/config.hpp>
#include <sprout/functional/equal_to.hpp>

namespace sprout {
	//
	// equal_to_t
	// equal_to_
	//
	typedef sprout::equal_to<> equal_to_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::equal_to_t equal_to_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_EQUAL_TO_HPP
