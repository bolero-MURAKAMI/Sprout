/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CBRT_HPP
#define SPROUT_MATH_CBRT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_cbrt(float x) {
				return __builtin_cbrtf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_cbrt(double x) {
				return __builtin_cbrt(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_cbrt(long double x) {
				return __builtin_cbrtl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			cbrt_impl(T x) {
				return x < 0 ? -sprout::pow(-x, sprout::math::third<T>())
					: sprout::pow(x, sprout::math::third<T>())
					;
			}
		}	// namespace detail
		//
		// cbrt
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		cbrt(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_cbrt(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::cbrt_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}

		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		cbrt(IntType x) {
			return sprout::math::cbrt(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::cbrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CBRT_HPP
