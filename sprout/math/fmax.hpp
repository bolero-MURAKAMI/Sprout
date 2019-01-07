/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FMAX_HPP
#define SPROUT_MATH_FMAX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_fmax(float x, float y) {
				return __builtin_fmaxf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_fmax(double x, double y) {
				return __builtin_fmax(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_fmax(long double x, long double y) {
				return __builtin_fmaxl(x, y);
			}
#endif
		}	// namespace detail
		//
		// fmax
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fmax(FloatType x, FloatType y) {
			return sprout::math::isnan(y) ? x
				: sprout::math::isnan(x) ? y
				: y == -sprout::numeric_limits<FloatType>::infinity() ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? x
				: x == -sprout::numeric_limits<FloatType>::infinity() ? y
				: y == sprout::numeric_limits<FloatType>::infinity() ? y
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: x == 0 && y == 0 ? x
				: sprout::math::detail::builtin_fmax(x, y)
#else
				: x < y ? y : x
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
		fmax(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::fmax(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::fmax;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMAX_HPP
