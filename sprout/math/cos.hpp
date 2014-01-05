/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_COS_HPP
#define SPROUT_MATH_COS_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
//#include <sprout/math/detail/cosp.hpp>
//#include <sprout/math/detail/sinp.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
//#include <sprout/math/fabs.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/fmod.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_cos(float x) {
				return __builtin_cosf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_cos(double x) {
				return __builtin_cos(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_cos(long double x) {
				return __builtin_cosl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			cos_impl_1(T x2, std::size_t n, std::size_t last) {
				return last - n == 1
					? (n % 2 ? -1 : 1) * sprout::detail::pow_n(x2, n) / sprout::math::unchecked_factorial<T>(2 * n)
					: sprout::math::detail::cos_impl_1(x2, n, n + (last - n) / 2)
						+ sprout::math::detail::cos_impl_1(x2, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cos_impl(T x) {
				return T(1) + sprout::math::detail::cos_impl_1(
					sprout::detail::pow2(sprout::math::fmod(x, sprout::math::two_pi<T>())),
					1, sprout::math::factorial_limit<T>() / 2 + 1
					);
			}

			// !!! OLD:
//			template<typename T>
//			inline SPROUT_CONSTEXPR T
//			cos_impl_2(T x) {
//				return x <= sprout::math::quarter_pi<T>() ? -sprout::math::detail::cosp(x)
//					: x <= sprout::math::half_pi<T>() ? -sprout::math::detail::sinp(sprout::math::half_pi<T>() - x)
//					: x <= sprout::math::three_quarters_pi<T>() ? sprout::math::detail::sinp(x - sprout::math::half_pi<T>())
//					: sprout::math::detail::cosp(sprout::math::pi<T>() - x)
//					;
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR T
//			cos_impl_1(T x) {
//				return x > sprout::math::pi<T>() ? sprout::math::detail::cos_impl_2(x - sprout::math::pi<T>())
//					: x <= sprout::math::quarter_pi<T>() ? sprout::math::detail::cosp(x)
//					: x <= sprout::math::half_pi<T>() ? sprout::math::detail::sinp(sprout::math::half_pi<T>() - x)
//					: x <= sprout::math::three_quarters_pi<T>() ? -sprout::math::detail::sinp(x - sprout::math::half_pi<T>())
//					: -sprout::math::detail::cosp(sprout::math::pi<T>() - x)
//					;
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR T
//			cos_impl(T x) {
//				return sprout::math::detail::cos_impl_1(sprout::math::fmod(sprout::math::fabs(x), sprout::math::two_pi<T>()));
//			}
		}	// namespace detail
		//
		// cos
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		cos(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? -sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_cos(x)
#else
				: x == 0 ? FloatType(1)
				: static_cast<FloatType>(sprout::math::detail::cos_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		cos(IntType x) {
			return sprout::math::cos(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::cos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COS_HPP
