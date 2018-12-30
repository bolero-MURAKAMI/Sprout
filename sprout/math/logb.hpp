/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOGB_HPP
#define SPROUT_MATH_LOGB_HPP

#include <cstdint>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log_a.hpp>
#include <sprout/math/trunc.hpp>
#include <sprout/math/itrunc.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_logb(float x) {
				return __builtin_logbf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_logb(double x) {
				return __builtin_logb(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_logb(long double x) {
				return __builtin_logbl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_3_neg_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_3_neg_lo(
						x, x0 * sprout::numeric_limits<T>::radix, x / (x0 / sprout::numeric_limits<T>::radix), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_3_neg_hi(T x, T x0, T base, T exp) {
				return !(base < sprout::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_3_neg_hi(
						x, x0 / sprout::numeric_limits<T>::radix, x / (x0 * sprout::numeric_limits<T>::radix), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_3_pos_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_3_pos_lo(
						x, x0 * sprout::numeric_limits<T>::radix, x / (x0 / sprout::numeric_limits<T>::radix), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_3_pos_hi(T x, T x0, T base, T exp) {
				return !(base < sprout::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_3_pos_hi(
						x, x0 / sprout::numeric_limits<T>::radix, x / (x0 * sprout::numeric_limits<T>::radix), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_3(T x, T x0, T base, T exp) {
				return x < 1
					? base < 1 ? sprout::math::detail::logb_impl_3_neg_lo(
							x, x0 * sprout::numeric_limits<T>::radix, x / (x0 / sprout::numeric_limits<T>::radix), exp - 1
							)
						: !(base < sprout::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_3_neg_hi(
								x, x0 / sprout::numeric_limits<T>::radix, x / (x0 * sprout::numeric_limits<T>::radix), exp + 1
								)
						: exp
					: base < 1 ? sprout::math::detail::logb_impl_3_pos_lo(
							x, x0 * sprout::numeric_limits<T>::radix, x / (x0 / sprout::numeric_limits<T>::radix), exp - 1
							)
						: !(base < sprout::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_3_pos_hi(
								x, x0 / sprout::numeric_limits<T>::radix, x / (x0 * sprout::numeric_limits<T>::radix), exp + 1
								)
						: exp
						;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2(T x, T x0, T exp) {
				return sprout::math::detail::logb_impl_3(x, x0, x / x0, exp);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_1(T x, T exp) {
				return sprout::math::detail::logb_impl_2(
					x, sprout::detail::pow_n(T(sprout::numeric_limits<T>::radix), sprout::math::itrunc<std::intmax_t>(exp)), exp
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl(T x) {
				return x < 0 ? sprout::math::detail::logb_impl_1(-x, sprout::math::trunc(sprout::math::log_a(T(sprout::numeric_limits<T>::radix), -x)))
					: sprout::math::detail::logb_impl_1(x, sprout::math::trunc(sprout::math::log_a(T(sprout::numeric_limits<T>::radix), x)))
					;
			}
		}	// namespace detail
		//
		// logb
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		logb(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == 0 ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	if defined(__GNUC__)
				: x == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::numeric_limits<FloatType>::infinity()
#	endif
				: sprout::math::detail::builtin_logb(x)
#else
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? sprout::numeric_limits<FloatType>::infinity()
				: static_cast<FloatType>(sprout::math::detail::logb_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		logb(IntType x) {
			return sprout::math::logb(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::logb;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOGB_HPP
