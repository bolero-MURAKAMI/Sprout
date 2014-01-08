/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_COPYSIGN_HPP
#define SPROUT_MATH_COPYSIGN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_copysign(float x, float y) {
				return __builtin_copysignf(x, y);
			}
			inline SPROUT_CONSTEXPR double
			builtin_copysign(double x, double y) {
				return __builtin_copysign(x, y);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_copysign(long double x, long double y) {
				return __builtin_copysignl(x, y);
			}
#endif
		}	// namespace detail
		//
		// copysign
		//
		// issue:
		//	[ !SPROUT_USE_BUILTIN_CMATH_FUNCTION ]
		//	copysign(Å}x, -0) returns -x for |x| is not 0 .
		//		# returns +x . ( same as copysign(Å}x, +0) )
		//	copysign(Å}x, -NaN) returns -x for |x| is not NaN .
		//		# returns +x . ( same as copysign(Å}x, +NaN) )
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		copysign(FloatType x, FloatType y) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_copysign(x, y)
#else
				x == 0
					? y == 0 ? y
						: sprout::math::signbit(y) ? -FloatType(0)
						: FloatType(0)
				: sprout::math::isnan(x)
					? sprout::math::isnan(y) ? y
						: sprout::math::signbit(y) ? -sprout::numeric_limits<FloatType>::quiet_NaN()
						: sprout::numeric_limits<FloatType>::quiet_NaN()
				: sprout::math::signbit(y) != sprout::math::signbit(x) ? -x
				: x
#endif
				;
		}

		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		copysign(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::copysign(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::copysign;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COPYSIGN_HPP
