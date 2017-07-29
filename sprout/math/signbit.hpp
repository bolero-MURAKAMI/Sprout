/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SIGNBIT_HPP
#define SPROUT_MATH_SIGNBIT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename FloatType>
			inline SPROUT_CONSTEXPR bool
			builtin_signbit(FloatType x) {
				return __builtin_signbit(x);
			}
#endif
		}	// namespace detail
		//
		// signbit
		//
		// issue:
		//	[ !(SPROUT_USE_BUILTIN_CMATH_FUNCTION || SPROUT_USE_BUILTIN_COPYSIGN_FUNCTION) ]
		//	signbit(-0) returns false .
		//		# returns true . ( same as signbit(+0) )
		//	signbit(-NaN) returns false .
		//		# returns true . ( same as signbit(+NaN) )
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		signbit(FloatType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_signbit(x)
#elif SPROUT_USE_BUILTIN_COPYSIGN_FUNCTION
				sprout::math::copysign(FloatType(1), x) < FloatType(0)
#else
				sprout::math::detail::broken_signbit(x)
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		signbit(IntType x) {
			return x < 0;
		}
	}	// namespace math

	using sprout::math::signbit;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIGNBIT_HPP
