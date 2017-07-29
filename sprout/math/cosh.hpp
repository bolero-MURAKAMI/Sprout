/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_COSH_HPP
#define SPROUT_MATH_COSH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_cosh(float x) {
				return __builtin_coshf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_cosh(double x) {
				return __builtin_cosh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_cosh(long double x) {
				return __builtin_coshl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosh_impl_1(T t) {
				return T(0.5) * t + T(0.5) / t;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosh_impl(T x) {
				return sprout::math::detail::cosh_impl_1(sprout::math::exp(x));
			}
		}	// namespace detail
		//
		// cosh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		cosh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_cosh(x)
#else
				: x == 0 ? FloatType(1)
				: static_cast<FloatType>(sprout::math::detail::cosh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		cosh(IntType x) {
			return sprout::math::cosh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::cosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COSH_HPP
