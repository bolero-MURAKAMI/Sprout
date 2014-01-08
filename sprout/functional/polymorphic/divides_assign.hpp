/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_ASSIGN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_ASSIGN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/divides_assign.hpp>

namespace sprout {
	//
	// divides_assign_t
	// divides_assign_
	//
	typedef sprout::divides_assign<> divides_assign_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::divides_assign_t divides_assign_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEVIDES_ASSIGN_HPP
