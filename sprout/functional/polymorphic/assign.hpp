/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ASSIGN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_ASSIGN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/assign.hpp>

namespace sprout {
	//
	// assign_t
	// assign_
	//
	typedef sprout::assign<> assign_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::assign_t assign_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ASSIGN_HPP
