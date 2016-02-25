/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOG10_HPP
#define SPROUT_MATH_LOG10_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_log10(float x) {
				return __builtin_log10f(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_log10(double x) {
				return __builtin_log10(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_log10(long double x) {
				return __builtin_log10l(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			log10_impl(T x) {
				return sprout::math::log(x) / sprout::math::ln_ten<T>();
			}
		}	// namespace detail
		//
		// log10
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		log10(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == 0 ? -sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x < 0 ? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_log10(x)
#else
				: x == 1 ? FloatType(0)
				: static_cast<FloatType>(sprout::math::detail::log10_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		log10(IntType x) {
			return sprout::math::log10(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::log10;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG10_HPP
