/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_MULTIPOLAR_HPP
#define SPROUT_MATH_QUATERNION_MULTIPOLAR_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// multipolar
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		multipolar(T const& rho1, T const& theta1, T const& rho2, T const& theta2) {
			return sprout::math::quaternion<T>(
				rho1 * sprout::math::cos(theta1),
				rho1 * sprout::math::sin(theta1),
				rho2 * sprout::math::cos(theta2),
				rho2 * sprout::math::sin(theta2)
				);
		}
	}	// namespace math

	using sprout::math::multipolar;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_MULTIPOLAR_HPP
