/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_DETAIL_MUL_HPP
#define SPROUT_MATH_QUATERNION_DETAIL_MUL_HPP

#include <sprout/config.hpp>
#include <sprout/array/array.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 2>
			mul(sprout::array<T, 2> const& l, T const& r) {
				return sprout::array<T, 2>{{
					l[0] * r,
					l[1] * r,
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 2>
			mul(sprout::array<T, 2> const& l, sprout::array<T, 2> const& r) {
				return sprout::array<T, 2>{{
					l[0] * r[0],
					l[1] * r[1],
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 4>
			mul(sprout::array<T, 4> const& l, T const& r) {
				return sprout::array<T, 4>{{
					l[0] * r,
					l[1] * r,
					l[2] * r,
					l[3] * r
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 4>
			mul(sprout::array<T, 4> const& l, sprout::array<T, 4> const& r) {
				return sprout::array<T, 4>{{
					l[0] * r[0],
					l[1] * r[1],
					l[2] * r[2],
					l[3] * r[3]
					}};
			}
		}	// namespace detail
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_DETAIL_MUL_HPP
