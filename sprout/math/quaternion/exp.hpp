/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_EXP_HPP
#define SPROUT_MATH_QUATERNION_EXP_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/exp.hpp>
//#include <sprout/math/sinc.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/math/quaternion/real.hpp>
#include <sprout/math/quaternion/unreal.hpp>
#include <sprout/math/quaternion/abs.hpp>

namespace sprout {
	namespace math {
		//
		// exp
		//
		// !!!
//		namespace detail {
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			exp_impl_1(sprout::math::quaternion<T> const& q, T const& z, T const& w) {
//				return sprout::math::exp(sprout::math::real(q)) * sprout::math::quaternion<T>(
//					sprout::math::cos(z),
//					w * q.R_component_2(),
//					w * q.R_component_3(),
//					w * q.R_component_4()
//					);
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			exp_impl(sprout::math::quaternion<T> const& q, T const& z) {
//				return sprout::math::detail::exp_impl_1(
//					q, z,
//					sprout::math::sinc_pi(z)
//					);
//			}
//		}	// namespace detail
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		exp(sprout::math::quaternion<T> const& q) {
//			return sprout::math::detail::exp_impl(
//				q,
//				sprout::math::abs(sprout::math::unreal(q))
//				);
//		}
	}	// namespace math

//	using sprout::math::exp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_EXP_HPP
