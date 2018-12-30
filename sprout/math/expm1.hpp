/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_EXPM1_HPP
#define SPROUT_MATH_EXPM1_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_expm1(float x) {
				return __builtin_expm1f(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_expm1(double x) {
				return __builtin_expm1(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_expm1(long double x) {
				return __builtin_expm1l(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			expm1_impl(T x) {
				return sprout::math::exp(x) - T(1);
			}
		}	// namespace detail
		//
		// expm1
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		expm1(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(-1)
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_expm1(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::expm1_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		expm1(IntType x) {
			return sprout::math::expm1(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::expm1;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXPM1_HPP
