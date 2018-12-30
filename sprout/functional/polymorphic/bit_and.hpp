/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_AND_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_AND_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bit_and.hpp>

namespace sprout {
	//
	// bit_and_t
	// bit_and_
	//
	typedef sprout::bit_and<> bit_and_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::bit_and_t bit_and_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_AND_HPP
