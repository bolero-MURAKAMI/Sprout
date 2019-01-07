/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ERFC_HPP
#define SPROUT_MATH_ERFC_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/erf.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_erfc(float x) {
				return __builtin_erfcf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_erfc(double x) {
				return __builtin_erfc(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_erfc(long double x) {
				return __builtin_erfcl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			erfc_impl(T x) {
				return T(1) - sprout::math::erf(x);
			}
		}	// namespace detail
		//
		// erfc
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		erfc(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? FloatType(0)
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(2)
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_erfc(x)
#else
				: static_cast<FloatType>(sprout::math::detail::erfc_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		erfc(IntType x) {
			return sprout::math::erfc(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::erfc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ERFC_HPP
