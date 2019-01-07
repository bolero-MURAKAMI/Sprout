/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_UNREAL_HPP
#define SPROUT_MATH_QUATERNION_UNREAL_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// unreal
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		unreal(sprout::math::quaternion<T> const& q) {
			return q.unreal();
		}
	}	// namespace math

	using sprout::math::unreal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_UNREAL_HPP
