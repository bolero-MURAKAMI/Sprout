/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LDEXP_HPP
#define SPROUT_MATH_LDEXP_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_ldexp(float x, int exp) {
				return __builtin_ldexpf(x, exp);
			}
			inline SPROUT_CONSTEXPR double
			builtin_ldexp(double x, int exp) {
				return __builtin_ldexp(x, exp);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_ldexp(long double x, int exp) {
				return __builtin_ldexpl(x, exp);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			ldexp_impl(T x, int exp) {
				return x * sprout::detail::pow_n(T(2), exp);
			}
		}	// namespace detail
		//
		// ldexp
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		ldexp(FloatType x, int exp) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_ldexp(x, exp)
#else
				sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
				: exp == 0 ? x
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::ldexp_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x), exp))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		ldexp(IntType x, int exp) {
			return sprout::math::ldexp(static_cast<double>(x), exp);
		}
	}	// namespace math

	using sprout::math::ldexp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LDEXP_HPP
