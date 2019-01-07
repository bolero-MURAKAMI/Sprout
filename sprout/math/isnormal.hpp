/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ISNORMAL_HPP
#define SPROUT_MATH_ISNORMAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/issubnormal.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename FloatType>
			inline SPROUT_CONSTEXPR bool
			builtin_isnormal(FloatType x) {
				return __builtin_isnormal(x);
			}
#endif
		}	// namespace detail
		//
		// isnormal
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		isnormal(FloatType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_isnormal(x)
#else
				!sprout::math::isnan(x)
				&& !sprout::math::isinf(x)
				&& !sprout::math::detail::issubnormal_or_zero(x)
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		isnormal(IntType x) {
			return x != 0;
		}
	}	// namespace math

	using sprout::math::isnormal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISNORMAL_HPP
