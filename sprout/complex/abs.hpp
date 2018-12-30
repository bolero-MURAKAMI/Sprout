/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ABS_HPP
#define SPROUT_COMPLEX_ABS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/norm.hpp>
#include <sprout/math/sqrt.hpp>

namespace sprout {
	//
	// abs
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T
	abs(sprout::complex<T> const& x) {
		return sprout::math::sqrt(sprout::norm(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ABS_HPP
