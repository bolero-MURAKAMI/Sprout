/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_DETAIL_SINP_HPP
#define SPROUT_MATH_DETAIL_SINP_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinp_impl(T x, T x2) {
				return x + x * (((((((
					1.58962301576546568060e-10) * x2
					- 2.50507477628578072866e-8) * x2
					+ 2.75573136213857245213e-6) * x2
					- 1.98412698295895385996e-4) * x2
					+ 8.33333333332211858878e-3) * x2
					- 1.66666666666666307295e-1) * x2
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinp(T x) {
				return sprout::math::detail::sinp_impl(x, x * x);
			}
		}	// namespace detail
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_DETAIL_SINP_HPP
