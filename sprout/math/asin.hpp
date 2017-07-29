/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ASIN_HPP
#define SPROUT_MATH_ASIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_asin(float x) {
				return __builtin_asinf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_asin(double x) {
				return __builtin_asin(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_asin(long double x) {
				return __builtin_asinl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_center_1(T x, T x2) {
				return ((((((((((((
					+ 0.0316658385792867081040808) * x2
					+ -0.0158620440988475212803145) * x2
					+ 0.0192942786775238654913582) * x2
					+ 0.0066153165197009078340075) * x2
					+ 0.0121483892822292648695383) * x2
					+ 0.0138885410156894774969889) * x2
					+ 0.0173593516996479249428647) * x2
					+ 0.0223717830666671020710108) * x2
					+ 0.0303819580081956423799529) * x2
					+ 0.0446428568582815922683933) * x2
					+ 0.0750000000029696112392353) * x2
					+ 0.1666666666666558995379880) * x2
					* x + x
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_center(T x) {
				return sprout::math::detail::asin_impl_center_1(x, x * x);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_tail(T x) {
				return sprout::math::half_pi<T>() + sprout::math::sqrt(T(1) - x)
					* (((((((((((((
						+ -0.0000121189820098929624806) * x
						+ 0.0001307564187657962919394) * x
						+ -0.0006702485124770180942917) * x
						+ 0.0021912255981979442677477) * x
						+ -0.0052049731575223952626203) * x
						+ 0.0097868293573384001221447) * x
						+ -0.0156746038587246716524035) * x
						+ 0.0229883479552557203133368) * x
						+ -0.0331919619444009606270380) * x
						+ 0.0506659694457588602631748) * x
						+ -0.0890259194305537131666744) * x
						+ 0.2145993335526539017488949) * x
						+ -1.5707961988153774692344105)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl(T x) {
				return x < T(-0.5) ? -sprout::math::detail::asin_impl_tail(-x)
					: x > T(0.5) ? sprout::math::detail::asin_impl_tail(x)
					: sprout::math::detail::asin_impl_center(x)
					;
			}
		}	// namespace detail
		//
		// asin
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		asin(FloatType x) {
			return sprout::math::isnan(x) ? x
				: sprout::math::fabs(x) > 1 ? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_asin(x)
#else
				: x == 0 ? x
				: static_cast<FloatType>(
					x < 0 ? -sprout::math::detail::asin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(-x))
						: sprout::math::detail::asin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x))
					)
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		asin(IntType x) {
			return sprout::math::asin(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::asin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASIN_HPP
