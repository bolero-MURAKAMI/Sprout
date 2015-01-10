/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MULTIPLIES_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_MULTIPLIES_HPP

#include <sprout/config.hpp>
#include <sprout/functional/multiplies.hpp>

namespace sprout {
	//
	// multiplies_t
	// multiplies_
	//
	typedef sprout::multiplies<> multiplies_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::multiplies_t multiplies_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MULTIPLIES_HPP
