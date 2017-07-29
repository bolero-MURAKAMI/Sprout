/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FDIM_HPP
#define SPROUT_MATH_FDIM_HPP

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
			builtin_fdim(float x, float y) {
				return __builtin_fdimf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_fdim(double x, double y) {
				return __builtin_fdim(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_fdim(long double x, long double y) {
				return __builtin_fdiml(x, y);
			}
#endif
		}	// namespace detail
		//
		// fdim
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fdim(FloatType x, FloatType y) {
			return sprout::math::isnan(y) ? y
				: sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(0)
				: y == sprout::numeric_limits<FloatType>::infinity() ? FloatType(0)
				: y == -sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_fdim(x, y)
#else
				: x > y ? x - y : FloatType(0)
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
		fdim(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::fdim(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::fdim;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FDIM_HPP
