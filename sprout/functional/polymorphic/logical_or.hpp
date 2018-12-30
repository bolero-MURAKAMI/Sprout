/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_OR_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_OR_HPP

#include <sprout/config.hpp>
#include <sprout/functional/logical_or.hpp>

namespace sprout {
	//
	// logical_or_t
	// logical_or_
	//
	typedef sprout::logical_or<> logical_or_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::logical_or_t logical_or_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_OR_HPP
