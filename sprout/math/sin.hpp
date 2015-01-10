/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SIN_HPP
#define SPROUT_MATH_SIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_sin(float x) {
				return __builtin_sinf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_sin(double x) {
				return __builtin_sin(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_sin(long double x) {
				return __builtin_sinl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			sin_impl(T x) {
				return -sprout::math::cos(x + sprout::math::half_pi<T>());
			}
		}	// namespace detail
		//
		// sin
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		sin(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? -sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_sin(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::sin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		sin(IntType x) {
			return sprout::math::sin(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::sin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIN_HPP
