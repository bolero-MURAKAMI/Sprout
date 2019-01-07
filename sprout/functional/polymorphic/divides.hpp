/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_HPP

#include <sprout/config.hpp>
#include <sprout/functional/divides.hpp>

namespace sprout {
	//
	// divides_t
	// divides_
	//
	typedef sprout::divides<> divides_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::divides_t divides_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_HPP
