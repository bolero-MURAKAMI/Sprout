/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_OR_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_OR_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bit_or.hpp>

namespace sprout {
	//
	// bit_or_t
	// bit_or_
	//
	typedef sprout::bit_or<> bit_or_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::bit_or_t bit_or_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_OR_HPP
