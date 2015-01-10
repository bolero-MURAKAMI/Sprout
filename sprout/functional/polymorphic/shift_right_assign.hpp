/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_ASSIGN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_ASSIGN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/shift_right_assign.hpp>

namespace sprout {
	//
	// shift_right_assign_t
	// shift_right_assign_
	//
	typedef sprout::shift_right_assign<> shift_right_assign_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::shift_right_assign_t shift_right_assign_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_ASSIGN_HPP
