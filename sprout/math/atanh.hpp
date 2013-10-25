/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ATANH_HPP
#define SPROUT_MATH_ATANH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_atanh(float x) {
				return __builtin_atanhf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_atanh(double x) {
				return __builtin_atanh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_atanh(long double x) {
				return __builtin_atanhl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			atanh_impl(T x) {
				return sprout::math::log((1 + x) / (1 - x)) / 2;
			}
		}	// namespace detail
		//
		// atanh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		atanh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == 1 ? sprout::numeric_limits<FloatType>::infinity()
				: x == -1 ? -sprout::numeric_limits<FloatType>::infinity()
				: sprout::math::fabs(x) > 1 ? -sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_atanh(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::atanh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		atanh(IntType x) {
			return sprout::math::atanh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::atanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATANH_HPP
