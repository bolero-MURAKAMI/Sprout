/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP

#include <sprout/config.hpp>
#include <sprout/functional/address_of.hpp>

namespace sprout {
	//
	// address_of_t
	// address_of_
	//
	typedef sprout::address_of<> address_of_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::address_of_t address_of_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP
