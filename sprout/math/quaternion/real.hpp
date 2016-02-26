/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_REAL_HPP
#define SPROUT_MATH_QUATERNION_REAL_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// real
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T
		real(sprout::math::quaternion<T> const& q) {
			return q.real();
		}
	}	// namespace math

	using sprout::math::real;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_REAL_HPP
