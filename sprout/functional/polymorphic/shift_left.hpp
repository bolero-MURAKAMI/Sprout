/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/shift_left.hpp>

namespace sprout {
	//
	// shift_left_t
	// shift_left_
	//
	typedef sprout::shift_left<> shift_left_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::shift_left_t shift_left_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_SHIFT_LEFT_HPP
