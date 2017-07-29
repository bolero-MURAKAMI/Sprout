/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_CYLINDROSPERICAL_HPP
#define SPROUT_MATH_QUATERNION_CYLINDROSPERICAL_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// cylindrospherical
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		cylindrospherical(T const& t, T const& radius, T const& longitude, T const& latitude) {
			return sprout::math::quaternion<T>(
				t,
				radius * sprout::math::cos(longitude) * sprout::math::cos(latitude),
				radius * sprout::math::sin(longitude) * sprout::math::cos(latitude),
				radius * sprout::math::sin(latitude)
				);
		}
	}	// namespace math

	using sprout::math::cylindrospherical;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_CYLINDROSPERICAL_HPP
