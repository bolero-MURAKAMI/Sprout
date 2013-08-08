/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FRAC_INT_HPP
#define SPROUT_MATH_FRAC_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/integer_part.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, T>
			frac_int_impl(T x, T ipart) {
				typedef sprout::pair<T, T> type;
				return sprout::math::isnan(x) ? type(x, ipart)
					: x == sprout::numeric_limits<T>::infinity() || x == -sprout::numeric_limits<T>::infinity() ? type(sprout::math::copysign(T(0), x), ipart)
					: x == 0 ? type(x, ipart)
					: x == ipart ? type(T(0) * x, ipart)
					: type(sprout::math::copysign(x - ipart, x), ipart)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, FloatType>
			frac_int(FloatType x) {
				return sprout::math::detail::frac_int_impl(x, sprout::integer_part(x));
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<double, double>
			frac_int(IntType x) {
				return sprout::math::detail::frac_int(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::frac_int;
	}	// namespace math

	using sprout::math::frac_int;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FRAC_INT_HPP
