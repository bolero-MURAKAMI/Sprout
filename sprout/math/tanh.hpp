/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_TANH_HPP
#define SPROUT_MATH_TANH_HPP

#include <type_traits>
#include <sprout/config.hpp>
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
			builtin_tanh(float x) {
				return __builtin_tanhf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_tanh(double x) {
				return __builtin_tanh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_tanh(long double x) {
				return __builtin_tanhl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			tanh_impl_2(T t, T u) {
				return (t - u) / (t + u);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			tanh_impl_1(T t) {
				return sprout::math::detail::tanh_impl_2(t, T(1) / t);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			tanh_impl(T x) {
				return sprout::math::detail::tanh_impl_1(sprout::math::exp(x));
			}
		}	// namespace detail
		//
		// tanh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		tanh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? FloatType(1)
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(-1)
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_tanh(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::tanh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		tanh(IntType x) {
			return sprout::math::tanh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::tanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TANH_HPP
