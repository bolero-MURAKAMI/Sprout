/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_CONJ_HPP
#define SPROUT_MATH_QUATERNION_CONJ_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// conj
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		conj(sprout::math::quaternion<T> const& q) {
			return sprout::math::quaternion<T>(
				+q.R_component_1(),
				-q.R_component_2(),
				-q.R_component_3(),
				-q.R_component_4()
				);
		}
	}	// namespace math

	using sprout::math::conj;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_CONJ_HPP
