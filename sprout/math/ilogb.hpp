/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ILOGB_HPP
#define SPROUT_MATH_ILOGB_HPP

#include <climits>
#include <cfloat>
#include <cmath>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/logb.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iszero.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR int
			builtin_ilogb(float x) {
				return __builtin_ilogbf(x);
			}
			inline SPROUT_CONSTEXPR int
			builtin_ilogb(double x) {
				return __builtin_ilogb(x);
			}
			inline SPROUT_CONSTEXPR int
			builtin_ilogb(long double x) {
				return __builtin_ilogbl(x);
			}
#endif
		}	// namespace detail
		//
		// ilogb
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb(FloatType x) {
			return sprout::math::iszero(x) ? FP_ILOGB0
				: sprout::math::isinf(x) ? INT_MAX
				: sprout::math::isnan(x) ? FP_ILOGBNAN
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_ilogb(x)
#else
				: static_cast<int>(sprout::math::logb(x))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb(IntType x) {
			return sprout::math::ilogb(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::ilogb;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ILOGB_HPP
