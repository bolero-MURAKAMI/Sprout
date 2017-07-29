/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POSITE_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_POSITE_HPP

#include <sprout/config.hpp>
#include <sprout/functional/posite.hpp>

namespace sprout {
	//
	// posite_t
	// posite_
	//
	typedef sprout::posite<> posite_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::posite_t posite_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POSITE_HPP
