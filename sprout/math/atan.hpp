/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ATAN_HPP
#define SPROUT_MATH_ATAN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_atan(float x) {
				return __builtin_atanf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_atan(double x) {
				return __builtin_atan(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_atan(long double x) {
				return __builtin_atanl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? (n % 2 ? -1 : 1) * sprout::detail::pow_n(x, 2 * n + 1) / (2 * n + 1)
					: sprout::math::detail::atan_impl_1(x, n, n + (last - n) / 2)
						+ sprout::math::detail::atan_impl_1(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan_impl(T x) {
				return x > sprout::math::root_two<T>() + 1
						? sprout::math::half_pi<T>() - sprout::math::detail::atan_impl_1(1 / x, 0, sprout::math::factorial_limit<T>() + 1)
					: x > sprout::math::root_two<T>() - 1
						? sprout::math::quarter_pi<T>() + sprout::math::detail::atan_impl_1((x - 1) / (x + 1), 0, sprout::math::factorial_limit<T>() + 1)
					: x + sprout::math::detail::atan_impl_1(x, 1, sprout::math::factorial_limit<T>() + 1)
					;
			}

		}	// namespace detail
		//
		// atan
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		atan(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::math::half_pi<FloatType>()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::math::half_pi<FloatType>()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_atan(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(
					x < 0 ? -sprout::math::detail::atan_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(-x))
						: sprout::math::detail::atan_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x))
					)
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		atan(IntType x) {
			return sprout::math::atan(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::atan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATAN_HPP
