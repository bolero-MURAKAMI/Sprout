/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_CONVERSION_HPP
#define SPROUT_RATIONAL_CONVERSION_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>

namespace sprout {
	//
	// rational_cast
	//
	template<typename T, typename IntType>
	inline SPROUT_CONSTEXPR T
	rational_cast(sprout::rational<IntType> const& src) {
		return static_cast<T>(src.numerator()) / static_cast<T>(src.denominator());
	}
}	// namespace sprout

#endif	// SPROUT_RATIONAL_CONVERSION_HPP
