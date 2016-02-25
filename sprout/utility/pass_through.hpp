/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PASS_THROUGH_HPP
#define SPROUT_UTILITY_PASS_THROUGH_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// pass_through
	//
	template<typename T>
	constexpr T&&
	pass_through(T&& t) {
		return static_cast<T&&>(t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOS_HPP
