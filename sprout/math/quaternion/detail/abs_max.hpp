/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_DETAIL_ABS_MAX_HPP
#define SPROUT_MATH_QUATERNION_DETAIL_ABS_MAX_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/range/algorithm/max_element.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			class abs_less {
			public:
				SPROUT_CONSTEXPR T
				operator()(T const& lhs, T const& rhs) const {
					return sprout::math::abs(lhs) < sprout::math::abs(rhs);
				}
			};

			template<typename T, std::size_t N>
			SPROUT_CONSTEXPR T
			abs_max(sprout::array<T, N> const& c) {
				return sprout::math::abs(*sprout::range::max_element(c, sprout::math::detail::abs_less<T>()));
			}
		}	// namespace detail
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_DETAIL_ABS_MAX_HPP
