/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_POW_HPP
#define SPROUT_MATH_QUATERNION_POW_HPP

#include <sprout/config.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// pow
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			pow_q_impl(sprout::math::quaternion<T> const& q, int n, int	m, sprout::math::quaternion<T> const& result) {
				return n != m << 1 ? result * result * q
					: result * result
					;
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		pow(sprout::math::quaternion<T> const& q, int n) {
			return n > 1 ? sprout::math::detail::pow_q_impl(
					q, n, n >> 1, sprout::math::pow(q, n >> 1)
					)
				: n == 1 ? q
				: n == 0 ? sprout::math::quaternion<T>(static_cast<T>(1))
				: sprout::math::pow(sprout::math::quaternion<T>(static_cast<T>(1)) / q, -n)
				;
		}
	}	// namespace math

	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_POW_HPP
