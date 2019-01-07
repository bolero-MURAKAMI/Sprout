/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_DETAIL_COSP_HPP
#define SPROUT_MATH_DETAIL_COSP_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosp_impl(T x2) {
				return (((((((
					-1.13585365213876817300e-11) * x2
					+ 2.08757008419747316778e-9) * x2
					- 2.75573141792967388112e-7) * x2
					+ 2.48015872888517045348e-5) * x2
					- 1.38888888888730564116e-3) * x2
					+ 4.16666666666665929218e-2) * x2
					- 0.5) * x2
					+ 1.0
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosp(T x) {
				return sprout::math::detail::cosp_impl(x * x);
			}
		}	// namespace detail
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_DETAIL_COSP_HPP
