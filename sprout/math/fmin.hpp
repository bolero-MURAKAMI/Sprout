/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FMIN_HPP
#define SPROUT_MATH_FMIN_HPP

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
			builtin_fmin(float x, float y) {
				return __builtin_fminf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_fmin(double x, double y) {
				return __builtin_fmin(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_fmin(long double x, long double y) {
				return __builtin_fminl(x, y);
			}
#endif
		}	// namespace detail
		//
		// fmin
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fmin(FloatType x, FloatType y) {
			return sprout::math::isnan(y) ? x
				: sprout::math::isnan(x) ? y
				: x == -sprout::numeric_limits<FloatType>::infinity() ? x
				: y == sprout::numeric_limits<FloatType>::infinity() ? x
				: y == -sprout::numeric_limits<FloatType>::infinity() ? y
				: x == sprout::numeric_limits<FloatType>::infinity() ? y
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: x == 0 && y == 0 ? x
				: sprout::math::detail::builtin_fmin(x, y)
#else
				: y < x ? y : x
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
		fmin(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::fmin(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::fmin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMIN_HPP
