/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOG2_HPP
#define SPROUT_MATH_LOG2_HPP

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
			builtin_log2(float x) {
				return __builtin_log2f(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_log2(double x) {
				return __builtin_log2(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_log2(long double x) {
				return __builtin_log2l(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			log2_impl(T x) {
				return sprout::math::log(x) / sprout::math::ln_two<T>();
			}
		}	// namespace detail
		//
		// log2
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		log2(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == 0 ? -sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x < 0 ? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_log2(x)
#else
				: x == 1 ? FloatType(0)
				: static_cast<FloatType>(sprout::math::detail::log2_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		log2(IntType x) {
			return sprout::math::log2(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::log2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG2_HPP
