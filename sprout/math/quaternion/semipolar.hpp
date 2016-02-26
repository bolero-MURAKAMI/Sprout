/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_SEMIPOLAR_HPP
#define SPROUT_MATH_QUATERNION_SEMIPOLAR_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// semipolar
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		semipolar(T const& rho, T const& alpha, T const& theta1, T const& theta2) {
			return rho * sprout::math::quaternion<T>(
				sprout::math::cos(alpha) * sprout::math::cos(theta1),
				sprout::math::cos(alpha) * sprout::math::sin(theta1),
				sprout::math::sin(alpha) * sprout::math::cos(theta2),
				sprout::math::sin(alpha) * sprout::math::sin(theta2)
				);
		}
	}	// namespace math

	using sprout::math::semipolar;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_SEMIPOLAR_HPP
