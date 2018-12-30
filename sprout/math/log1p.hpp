/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOG1P_HPP
#define SPROUT_MATH_LOG1P_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_log1p(float x) {
				return __builtin_log1pf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_log1p(double x) {
				return __builtin_log1p(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_log1p(long double x) {
				return __builtin_log1pl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			log1p_impl(T x) {
				return sprout::math::log(T(1) + x);
			}
		}	// namespace detail
		//
		// log1p
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		log1p(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == -1 ? -sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x < -1 ? -sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_log1p(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::log1p_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		log1p(IntType x) {
			return sprout::math::log1p(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::log1p;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG1P_HPP
