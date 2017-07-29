/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/shift_right.hpp>

namespace sprout {
	//
	// shift_right_t
	// shift_right_
	//
	typedef sprout::shift_right<> shift_right_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::shift_right_t shift_right_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP
