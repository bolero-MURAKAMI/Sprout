/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_NOT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_NOT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bit_not.hpp>

namespace sprout {
	//
	// bit_not_t
	// bit_not_
	//
	typedef sprout::bit_not<> bit_not_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::bit_not_t bit_not_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIT_NOT_HPP
