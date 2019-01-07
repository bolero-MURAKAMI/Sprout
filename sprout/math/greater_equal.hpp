/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_GREATER_EQUAL_HPP
#define SPROUT_MATH_GREATER_EQUAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType1, typename FloatType2,
				typename sprout::enabler_if<
					std::is_floating_point<typename sprout::arithmetic_promote<FloatType1, FloatType2>::type>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater_equal(FloatType1 x, FloatType2 y) {
				return sprout::math::equal_to(x, y) || x > y;
			}

			template<
				typename IntType1, typename IntType2,
				typename sprout::enabler_if<
					std::is_integral<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::value
					&& (sprout::is_unsigned<IntType1>::value == sprout::is_unsigned<IntType2>::value)
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater_equal(IntType1 x, IntType2 y) {
				return x >= y;
			}
			template<
				typename IntType1, typename IntType2,
				typename sprout::enabler_if<
					std::is_integral<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::value
					&& sprout::is_signed<IntType1>::value && sprout::is_unsigned<IntType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater_equal(IntType1 x, IntType2 y) {
				typedef typename std::make_unsigned<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::type type;
				return x < 0 ? false
					: static_cast<type>(x) >= static_cast<type>(y)
					;
			}
			template<
				typename IntType1, typename IntType2,
				typename sprout::enabler_if<
					std::is_integral<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::value
					&& sprout::is_unsigned<IntType1>::value && sprout::is_signed<IntType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater_equal(IntType1 x, IntType2 y) {
				typedef typename std::make_unsigned<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::type type;
				return y < 0 ? true
					: static_cast<type>(x) >= static_cast<type>(y)
					;
			}
		}	// namespace detail
		//
		// greater_equal
		//
		template<
			typename T, typename U,
			typename sprout::enabler_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		greater_equal(T x, U y) {
			return sprout::math::detail::greater_equal(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_GREATER_EQUAL_HPP
