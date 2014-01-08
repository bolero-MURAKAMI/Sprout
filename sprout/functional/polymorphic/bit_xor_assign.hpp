/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_ASSIGN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_ASSIGN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bit_xor_assign.hpp>

namespace sprout {
	//
	// bit_xor_assign_t
	// bit_xor_assign_
	//
	typedef sprout::bit_xor_assign<> bit_xor_assign_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::bit_xor_assign_t bit_xor_assign_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_XOR_ASSIGN_HPP
