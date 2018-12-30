/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SINH_HPP
#define SPROUT_MATH_SINH_HPP

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
			builtin_sinh(float x) {
				return __builtin_sinhf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_sinh(double x) {
				return __builtin_sinh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_sinh(long double x) {
				return __builtin_sinhl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinh_impl_1(T t) {
				return T(0.5) * t - T(0.5) / t;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinh_impl(T x) {
				return sprout::math::detail::sinh_impl_1(sprout::math::exp(x));
			}
		}	// namespace detail
		//
		// sinh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		sinh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_sinh(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::sinh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		sinh(IntType x) {
			return sprout::math::sinh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::sinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SINH_HPP
