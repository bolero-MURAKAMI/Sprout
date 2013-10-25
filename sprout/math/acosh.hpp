/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ACOSH_HPP
#define SPROUT_MATH_ACOSH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_acosh(float x) {
				return __builtin_acoshf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_acosh(double x) {
				return __builtin_acosh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_acosh(long double x) {
				return __builtin_acoshl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			acosh_impl(T x) {
				return sprout::math::log(x + sprout::math::sqrt(x * x - 1));
			}
		}	// namespace detail
		//
		// acosh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		acosh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x < 1 ? -sprout::numeric_limits<FloatType>::quiet_NaN()
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_acosh(x)
#else
				: x == 1 ? FloatType(0)
				: static_cast<FloatType>(sprout::math::detail::acosh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		acosh(IntType x) {
			return sprout::math::acosh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::acosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOSH_HPP
