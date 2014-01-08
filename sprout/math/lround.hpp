/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LROUND_HPP
#define SPROUT_MATH_LROUND_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iround.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR long
			builtin_lround(float x) {
				return __builtin_lroundf(x);
			}
			inline SPROUT_CONSTEXPR long
			builtin_lround(double x) {
				return __builtin_lround(x);
			}
			inline SPROUT_CONSTEXPR long
			builtin_lround(long double x) {
				return __builtin_lroundl(x);
			}
#endif
		}	// namespace detail
		//
		// lround
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR long
		lround(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<long>::min()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_lround(x)
#else
				: sprout::math::iround<long>(x);
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR long
		lround(IntType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_lround(x)
#else
				sprout::math::iround<long>(x)
#endif
				;
		}
	}	// namespace math

	using sprout::math::lround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LROUND_HPP
