/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_POW_HPP
#define SPROUT_MATH_POW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/is_integer.hpp>
#include <sprout/math/is_odd.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_pow(float x, float y) {
				return __builtin_powf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_pow(double x, double y) {
				return __builtin_pow(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_pow(long double x, long double y) {
				return __builtin_powl(x, y);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			pow_impl(T x, T y) {
				return sprout::math::exp(y * sprout::math::log(x));
			}
		}	// namespace detail
		//
		// pow
		//
		// issue:
		//	[ !SPROUT_USE_BUILTIN_CMATH_FUNCTION ]
		//	pow(-0, y) returns -Åá for y an odd integer < 0.
		//		# returns +Åá . ( same as pow(+0, y) )
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		pow(FloatType x, FloatType y) {
			return x == 1 ? FloatType(1)
				: y == 0 ? FloatType(1)
				: sprout::math::isnan(y) ? y
				: sprout::math::isnan(x) ? x
				: x == 0
					? y < 0
						? sprout::math::is_odd(y) ? sprout::math::copysign(sprout::numeric_limits<FloatType>::infinity(), x)
						: sprout::numeric_limits<FloatType>::infinity()
					: sprout::math::is_odd(y) ? x
					: FloatType(0)
				: x == -1 && (y == sprout::numeric_limits<FloatType>::infinity() || y == -sprout::numeric_limits<FloatType>::infinity()) ? FloatType(1)
				: y == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::math::fabs(x) < 1 ? sprout::numeric_limits<FloatType>::infinity()
					: FloatType(0)
				: y == sprout::numeric_limits<FloatType>::infinity()
					? sprout::math::fabs(x) < 1 ? FloatType(0)
					: sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity()
					? y < 0
						? sprout::math::is_odd(y) ? -FloatType(0)
						: FloatType(0)
					: sprout::math::is_odd(y) ? -sprout::numeric_limits<FloatType>::infinity()
					: sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity()
					? y < 0 ? FloatType(0)
					: sprout::numeric_limits<FloatType>::infinity()
				: x < 0 && !sprout::math::is_integer(y) ? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_pow(x, y)
#else
				: static_cast<FloatType>(sprout::math::detail::pow_impl(
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
		pow(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::pow(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_POW_HPP
