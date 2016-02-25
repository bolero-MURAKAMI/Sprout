/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LLROUND_HPP
#define SPROUT_MATH_LLROUND_HPP

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
			inline SPROUT_CONSTEXPR long long
			builtin_llround(float x) {
				return __builtin_llroundf(x);
			}
			inline SPROUT_CONSTEXPR long long
			builtin_llround(double x) {
				return __builtin_llround(x);
			}
			inline SPROUT_CONSTEXPR long long
			builtin_llround(long double x) {
				return __builtin_llroundl(x);
			}
#endif
		}	// namespace detail
		//
		// llround
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR long long
		llround(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<long long>::min()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_llround(x)
#else
				: sprout::math::iround<long long>(x);
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR long long
		llround(IntType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_llround(x)
#else
				sprout::math::iround<long long>(x)
#endif
				;
		}
	}	// namespace math

	using sprout::math::llround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LLROUND_HPP
