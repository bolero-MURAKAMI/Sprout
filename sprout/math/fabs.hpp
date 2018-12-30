/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FABS_HPP
#define SPROUT_MATH_FABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_fabs(float x) {
				return __builtin_fabsf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_fabs(double x) {
				return __builtin_fabs(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_fabs(long double x) {
				return __builtin_fabsl(x);
			}
#endif
		}	// namespace detail
		//
		// fabs
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fabs(FloatType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_fabs(x)
#else
				sprout::math::isnan(x) ? sprout::numeric_limits<FloatType>::quiet_NaN()
				: x == 0 ? FloatType(0)
				: sprout::math::copysign(x, FloatType(0))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		fabs(IntType x) {
			return sprout::math::fabs(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::fabs;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FABS_HPP
