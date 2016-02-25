/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_EXP_HPP
#define SPROUT_MATH_EXP_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_exp(float x) {
				return __builtin_expf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_exp(double x) {
				return __builtin_exp(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_exp(long double x) {
				return __builtin_expl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::detail::pow_n(x, n) / sprout::math::unchecked_factorial<T>(n)
					: sprout::math::detail::exp_impl_1(x, n, n + (last - n) / 2)
						+ sprout::math::detail::exp_impl_1(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp_impl(T x) {
				return !(x > -1) ? T(1) / (T(1) + sprout::math::detail::exp_impl_1(-x, 1, sprout::math::factorial_limit<T>() / 2 + 1))
					: T(1) + sprout::math::detail::exp_impl_1(x, 1, sprout::math::factorial_limit<T>() / 2 + 1)
					;
			}
		}	// namespace detail
		//
		// exp
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		exp(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(0)
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_exp(x)
#else
				: x == 0 ? FloatType(1)
				: static_cast<FloatType>(sprout::math::detail::exp_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		exp(IntType x) {
			return sprout::math::exp(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::exp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP_HPP
