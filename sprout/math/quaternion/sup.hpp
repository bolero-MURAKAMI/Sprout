/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_SUP_HPP
#define SPROUT_MATH_QUATERNION_SUP_HPP

#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/math/quaternion/detail/abs_max.hpp>

namespace sprout {
	namespace math {
		//
		// sup
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T
		sup(sprout::math::quaternion<T> const& q) {
			return sprout::math::detail::abs_max(
				sprout::array<T, 4>{{
					q.R_component_1(),
					q.R_component_2(),
					q.R_component_3(),
					q.R_component_4()
					}}
				);
		}
	}	// namespace math

	using sprout::math::sup;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_SUP_HPP
