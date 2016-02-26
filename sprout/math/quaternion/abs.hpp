/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_ABS_HPP
#define SPROUT_MATH_QUATERNION_ABS_HPP

#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/math/quaternion/detail/abs_max.hpp>
#include <sprout/math/quaternion/detail/sum.hpp>
#include <sprout/math/quaternion/detail/mul.hpp>

namespace sprout {
	namespace math {
		//
		// abs
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_3(sprout::array<T, 4> const& temp, T const& maxim) {
				return maxim * sprout::math::sqrt(sprout::math::detail::sum(sprout::math::detail::mul(temp, temp)));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_2(sprout::array<T, 4> const& temp, T const& maxim) {
				return sprout::math::detail::abs_q_impl_3(
					sprout::math::detail::mul(temp, maxim), maxim
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_1(sprout::array<T, 4> const& temp, T const& maxim) {
				return maxim == static_cast<T>(0) ? sprout::math::quaternion<T>(maxim)
					: sprout::math::detail::abs_q_impl_2(
						temp, static_cast<T>(1) / maxim
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl(sprout::array<T, 4> const& temp) {
				return sprout::math::detail::abs_q_impl_1(
					temp, sprout::math::detail::abs_max(temp)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR T
		abs(sprout::math::quaternion<T> const& q) {
			return sprout::math::detail::abs_q_impl(
				sprout::array<T, 4>{{
					q.R_component_1(),
					q.R_component_2(),
					q.R_component_3(),
					q.R_component_4()
					}}
				);
		}
	}	// namespace math

	using sprout::math::abs;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_ABS_HPP
