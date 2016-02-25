/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUOTIENT_HPP
#define SPROUT_MATH_QUOTIENT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/rem_quo.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		//
		// quotient
		//
		template<
			typename R = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<R>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR R
		quotient(FloatType x, FloatType y) {
			return y == 0 ? R(0)
				: sprout::math::isnan(y) || sprout::math::isnan(x) ? R(0)
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? R(0)
				: x == 0 ? R(0)
				: y == sprout::numeric_limits<FloatType>::infinity() || y == -sprout::numeric_limits<FloatType>::infinity() ? R(0)
				: sprout::math::rem_quo<R>(x, y).second
				;
		}
		template<
			typename R = int,
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value && std::is_integral<R>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR R
		quotient(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::quotient(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::quotient;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUOTIENT_HPP
