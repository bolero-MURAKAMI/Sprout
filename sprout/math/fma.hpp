/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FMA_HPP
#define SPROUT_MATH_FMA_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_fma(float x, float y, float z) {
				return __builtin_fmaf(x, y, z);
			}
			inline SPROUT_CONSTEXPR double
			builtin_fma(double x, double y, double z) {
				return __builtin_fma(x, y, z);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_fma(long double x, long double y, long double z) {
				return __builtin_fmal(x, y, z);
			}
#endif
		}	// namespace detail
		//
		// fma
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fma(FloatType x, FloatType y, FloatType z) {
			return sprout::math::isnan(x) ? x
				: sprout::math::isnan(y) ? y
				: sprout::math::isnan(z) ? z
				: sprout::math::isinf(x) && y == 0 ? sprout::numeric_limits<FloatType>::quiet_NaN()
				: sprout::math::isinf(y) && x == 0 ? sprout::numeric_limits<FloatType>::quiet_NaN()
				: (sprout::math::isinf(x) || sprout::math::isinf(y)) && sprout::math::isinf(z) && (sprout::math::signbit(x) ^ sprout::math::signbit(y) ^ sprout::math::signbit(z))
					? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_fma(x, y, z)
#else
				: x * y + z
#endif
				;
		}
		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename ArithmeticType3,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value
					&& std::is_arithmetic<ArithmeticType2>::value
					&& std::is_arithmetic<ArithmeticType3>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<
			ArithmeticType1, ArithmeticType2, ArithmeticType3
		>::type
		fma(ArithmeticType1 x, ArithmeticType2 y, ArithmeticType3 z) {
			typedef typename sprout::float_promote<
				ArithmeticType1, ArithmeticType2, ArithmeticType3
			>::type type;
			return sprout::math::fma(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
		}
	}	// namespace math

	using sprout::math::fma;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMA_HPP
