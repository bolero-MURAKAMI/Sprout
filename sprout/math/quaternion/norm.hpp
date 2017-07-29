/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_NORM_HPP
#define SPROUT_MATH_QUATERNION_NORM_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/math/quaternion/arithmetic_operators.hpp>
#include <sprout/math/quaternion/real.hpp>
#include <sprout/math/quaternion/conj.hpp>

namespace sprout {
	namespace math {
		//
		// norm
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T
		norm(sprout::math::quaternion<T> const& q) {
			return sprout::math::real(q * sprout::math::conj(q));
		}
	}	// namespace math

	using sprout::math::norm;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_NORM_HPP
