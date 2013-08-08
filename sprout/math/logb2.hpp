/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOGB2_HPP
#define SPROUT_MATH_LOGB2_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>
#if SPROUT_FLT_RADIX_IS_2
#	include <sprout/math/logb.hpp>
#else
#	include <cstdint>
#	include <sprout/limits.hpp>
#	include <sprout/detail/pow.hpp>
#	include <sprout/math/detail/float_compute.hpp>
#	include <sprout/math/isnan.hpp>
#	include <sprout/math/log_a.hpp>
#	include <sprout/math/trunc.hpp>
#	include <sprout/math/itrunc.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_FLT_RADIX_IS_2
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			logb2(FloatType x) {
				return sprout::math::logb(x);
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			logb2(IntType x) {
				return sprout::math::logb(x);
			}
#else
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_3_neg_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb2_impl_3_neg_lo(
						x, x0 * 2, x / (x0 / 2), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_3_neg_hi(T x, T x0, T base, T exp) {
				return !(base < 2) ? sprout::math::detail::logb2_impl_3_neg_hi(
						x, x0 / 2, x / (x0 * 2), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_3_pos_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb2_impl_3_pos_lo(
						x, x0 * 2, x / (x0 / 2), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_3_pos_hi(T x, T x0, T base, T exp) {
				return !(base < 2) ? sprout::math::detail::logb2_impl_3_pos_hi(
						x, x0 / 2, x / (x0 * 2), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_3(T x, T x0, T base, T exp) {
				return x < 1
					? base < 1 ? sprout::math::detail::logb2_impl_3_neg_lo(
							x, x0 * 2, x / (x0 / 2), exp - 1
							)
						: !(base < 2) ? sprout::math::detail::logb2_impl_3_neg_hi(
							x, x0 / 2, x / (x0 * 2), exp + 1
							)
						: exp
					: base < 1 ? sprout::math::detail::logb2_impl_3_pos_lo(
							x, x0 * 2, x / (x0 / 2), exp - 1
							)
						: !(base < 2) ? sprout::math::detail::logb2_impl_3_pos_hi(
							x, x0 / 2, x / (x0 * 2), exp + 1
							)
						: exp
						;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_2(T x, T x0, T exp) {
				return sprout::math::detail::logb2_impl_3(x, x0, x / x0, exp);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl_1(T x, T exp) {
				return sprout::math::detail::logb2_impl_2(
					x, sprout::detail::pow_n(T(2), sprout::math::itrunc<std::intmax_t>(exp)), exp
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb2_impl(T x) {
				return x < 0 ? sprout::math::detail::logb2_impl_1(-x, sprout::math::trunc(sprout::math::log_a(T(2), -x)))
					: sprout::math::detail::logb2_impl_1(x, sprout::math::trunc(sprout::math::log_a(T(2), x)))
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			logb2(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == 0 ? -sprout::numeric_limits<FloatType>::infinity()
					: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
						? sprout::numeric_limits<FloatType>::infinity()
					: static_cast<FloatType>(sprout::math::detail::logb2_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			logb2(IntType x) {
				return sprout::math::detail::logb2(static_cast<double>(x));
			}
#endif
		}	// namespace detail

		using sprout::math::detail::logb2;
	}	// namespace math

	using sprout::math::logb2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOGB2_HPP
