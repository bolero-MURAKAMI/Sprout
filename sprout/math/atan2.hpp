/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ATAN2_HPP
#define SPROUT_MATH_ATAN2_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/atan.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_atan2(float y, float x) {
				return __builtin_atan2f(y, x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_atan2(double y, double x) {
				return __builtin_atan2(y, x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_atan2(long double y, long double x) {
				return __builtin_atan2l(y, x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan2_impl(T y, T x) {
				return x < 0 ? sprout::math::atan(y / x) + (
						y < 0 ? -sprout::math::pi<T>()
							: sprout::math::pi<T>()
						)
					: sprout::math::atan(y / x)
					;
			}
		}	// namespace detail
		//
		// atan2
		//
		// issue:
		//	[ !(SPROUT_USE_BUILTIN_CMATH_FUNCTION || SPROUT_USE_BUILTIN_COPYSIGN_FUNCTION) ]
		//	atan2(Å}0, -0) returns Å}ÉŒ .
		//		# returns Å}0 . ( same as atan2(Å}0, +0) )
		//	atan2(-0, x) returns -ÉŒ for x < 0.
		//		# returns +ÉŒ . ( same as atan2(+0, x) )
		//	atan2(-NaN, -NaN) returns -NaN .
		//		# returns +NaN . ( same as atan2(+NaN, +NaN) )
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		atan2(FloatType y, FloatType x) {
			return sprout::math::isnan(y)
					? sprout::math::isnan(x)
						? sprout::math::signbit(y) && sprout::math::signbit(x) ? -sprout::numeric_limits<FloatType>::quiet_NaN()
							: sprout::numeric_limits<FloatType>::quiet_NaN()
						: y
				: sprout::math::isnan(x) ? x
				: x == -sprout::numeric_limits<FloatType>::infinity()
					? y == sprout::numeric_limits<FloatType>::infinity() ? sprout::math::three_quarters_pi<FloatType>()
						: y == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::math::three_quarters_pi<FloatType>()
						: sprout::math::copysign(sprout::math::pi<FloatType>(), y)
				: x == sprout::numeric_limits<FloatType>::infinity()
					? y == sprout::numeric_limits<FloatType>::infinity() ? sprout::math::quarter_pi<FloatType>()
						: y == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::math::quarter_pi<FloatType>()
						: FloatType(0) * y
				: y == sprout::numeric_limits<FloatType>::infinity() ? sprout::math::half_pi<FloatType>()
				: y == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::math::half_pi<FloatType>()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_atan2(y, x)
#else
				: y == 0
					? x < 0 ? sprout::math::copysign(sprout::math::pi<FloatType>(), y)
						: x > 0 ? FloatType(0) * y
						: sprout::math::signbit(x) ? sprout::math::copysign(sprout::math::pi<FloatType>(), y)
						: FloatType(0) * y
				: x == 0
					? y < 0 ? -sprout::math::half_pi<FloatType>()
						: sprout::math::half_pi<FloatType>()
				: static_cast<FloatType>(
					sprout::math::detail::atan2_impl(
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y),
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)
						)
					)
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
		atan2(ArithmeticType1 y, ArithmeticType2 x) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::atan2(static_cast<type>(y), static_cast<type>(x));
		}
	}	// namespace math

	using sprout::math::atan2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATAN2_HPP
