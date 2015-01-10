/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/logical_not.hpp>

namespace sprout {
	//
	// logical_not_t
	// logical_not_
	//
	typedef sprout::logical_not<> logical_not_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::logical_not_t logical_not_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP
