/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LOG_A_HPP
#define SPROUT_MATH_LOG_A_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/log.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_a_impl(T x, T y) {
				return x == 2 ? sprout::math::log(y) / sprout::math::ln_two<T>()
					: x == 10 ? sprout::math::log(y) / sprout::math::ln_ten<T>()
					: sprout::math::log(y) / sprout::math::log(x)
					;
			}
		}	// namespace detail
		//
		// log_a
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		log_a(FloatType x, FloatType y) {
			return static_cast<FloatType>(sprout::math::detail::log_a_impl(
				static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
				static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y)
				));
		}

		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		log_a(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::log_a(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::log_a;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG_A_HPP
