/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MODULUS_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_MODULUS_HPP

#include <sprout/config.hpp>
#include <sprout/functional/modulus.hpp>

namespace sprout {
	//
	// modulus_t
	// modulus_
	//
	typedef sprout::modulus<> modulus_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::modulus_t modulus_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MODULUS_HPP
