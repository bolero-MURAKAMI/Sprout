/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ISLESSGREATER_HPP
#define SPROUT_MATH_ISLESSGREATER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename FloatType>
			inline SPROUT_CONSTEXPR bool
			builtin_islessgreater(FloatType x, FloatType y) {
				return __builtin_islessgreater(x, y);
			}
#endif
		}	// namespace detail
		//
		// islessgreater
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		islessgreater(FloatType x, FloatType y) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_islessgreater(x, y)
#else
				!sprout::math::isnan(x) && !sprout::math::isnan(y) && ((x < y) || (x > y))
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
		inline SPROUT_CONSTEXPR bool
		islessgreater(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::islessgreater(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::islessgreater;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISLESSGREATER_HPP
