/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FPCLASSIFY_HPP
#define SPROUT_MATH_FPCLASSIFY_HPP

#include <cmath>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iszero.hpp>
#include <sprout/math/issubnormal.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename FloatType>
			inline SPROUT_CONSTEXPR int
			builtin_fpclassify(FloatType x) {
				return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x);
			}
#endif
		}	// namespace detail
		//
		// fpclassify
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		fpclassify(FloatType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_fpclassify(x)
#else
				sprout::math::isnan(x) ? FP_NAN
				: sprout::math::isinf(x) ? FP_INFINITE
				: sprout::math::iszero(x) ? FP_ZERO
				: sprout::math::detail::issubnormal_or_zero(x) ? FP_SUBNORMAL
				: FP_NORMAL
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		fpclassify(IntType x) {
			return x ? FP_NORMAL
				: FP_ZERO
				;
		}
	}	// namespace math

	using sprout::math::fpclassify;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FPCLASSIFY_HPP
