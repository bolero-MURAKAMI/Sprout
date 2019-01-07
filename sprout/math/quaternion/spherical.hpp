/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_SPHERICAL_HPP
#define SPROUT_MATH_QUATERNION_SPHERICAL_HPP

#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/quaternion/quaternion.hpp>

namespace sprout {
	namespace math {
		//
		// spherical
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			spherical_impl(T const& rho, T const& theta, T const& phi1, T const& phi2, T const& p1, T const& p2) {
				return rho * sprout::math::quaternion<T>(
					sprout::math::cos(theta) * (p2 * p1),
					sprout::math::sin(theta) * (p2 * p1),
					sprout::math::sin(phi1) * p2,
					sprout::math::sin(phi2)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		spherical(T const& rho, T const& theta, T const& phi1, T const& phi2) {
			return sprout::math::detail::spherical_impl(
				rho, theta, phi1, phi2,
				sprout::math::cos(phi1), sprout::math::cos(phi2)
				);
		}
	}	// namespace math

	using sprout::math::spherical;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_SPHERICAL_HPP
