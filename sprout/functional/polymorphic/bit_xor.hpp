/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bit_xor.hpp>

namespace sprout {
	//
	// bit_xor_t
	// bit_xor_
	//
	typedef sprout::bit_xor<> bit_xor_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::bit_xor_t bit_xor_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_HPP
