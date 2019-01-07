/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_CYLINDRICAL_HPP
#define SPROUT_MATH_QUATERNION_CYLINDRICAL_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// cylindrical
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		cylindrical(T const& r, T const& angle, T const& h1, T const& h2) {
			return sprout::math::quaternion<T>(
				r * sprout::math::cos(angle),
				r * sprout::math::sin(angle),
				h1,
				h2
				);
		}
	}	// namespace math

	using sprout::math::cylindrical;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_CYLINDRICAL_HPP
