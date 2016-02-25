/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_HYPOT_HPP
#define SPROUT_MATH_HYPOT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_hypot(float x, float y) {
				return __builtin_hypotf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_hypot(double x, double y) {
				return __builtin_hypot(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_hypot(long double x, long double y) {
				return __builtin_hypotl(x, y);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			hypot_impl_2(T t, T w) {
				return t * sprout::math::sqrt(T(1) + w * w);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			hypot_impl_1(T x, T y) {
				return x < y
					? sprout::math::detail::hypot_impl_2(y, x / y)
					: sprout::math::detail::hypot_impl_2(x, y / x)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			hypot_impl(T x, T y) {
				return sprout::math::detail::hypot_impl_1(sprout::math::fabs(x), sprout::math::fabs(y));
			}
		}	// namespace detail
		//
		// hypot
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		hypot(FloatType x, FloatType y) {
			return y == sprout::numeric_limits<FloatType>::infinity() || y == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::numeric_limits<FloatType>::infinity()
				: sprout::math::isnan(y) ? y
				: sprout::math::isnan(x) ? x
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_hypot(x, y)
#else
				: y == 0 ? sprout::math::fabs(x)
				: x == 0 ? sprout::math::fabs(y)
				: static_cast<FloatType>(sprout::math::detail::hypot_impl(
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y)
					))
#endif
				;
		}

		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		hypot(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::hypot(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::hypot;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_HYPOT_HPP
