/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SIGMOID_HPP
#define SPROUT_MATH_SIGMOID_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		//
		// sigmoid
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sigmoid_impl(T x){
				return 1 / (1 + sprout::math::exp(-x));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sigmoid_impl(T x, T a){
				return sprout::math::detail::sigmoid_impl(a * x);
			}
		}	// namespace detail
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		sigmoid(FloatType x){
			return sprout::math::detail::sigmoid_impl(sprout::math::detail::as_float_compute(x));
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		sigmoid(FloatType x, FloatType a){
			return sprout::math::detail::sigmoid_impl(sprout::math::detail::as_float_compute(x), sprout::math::detail::as_float_compute(a));
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		sigmoid(IntType x) {
			return sprout::math::sigmoid(static_cast<double>(x));
		}
		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		sigmoid(ArithmeticType1 x, ArithmeticType2 a) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::sigmoid(static_cast<type>(x), static_cast<type>(a));
		}

		//
		// d_sigmoid
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d_sigmoid_impl_1(T s){
				return s * (1 - s);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d_sigmoid_impl_1(T s, T a){
				return a * s * (1 - s);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d_sigmoid_impl(T x){
				return sprout::math::detail::d_sigmoid_impl_1(sprout::math::sigmoid(x));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d_sigmoid_impl(T x, T a){
				return sprout::math::detail::d_sigmoid_impl_1(sprout::math::sigmoid(x, a), a);
			}
		}	// namespace detail
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		d_sigmoid(FloatType x){
			return sprout::math::detail::d_sigmoid_impl(sprout::math::detail::as_float_compute(x));
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		d_sigmoid(FloatType x, FloatType a){
			return sprout::math::detail::d_sigmoid_impl(sprout::math::detail::as_float_compute(x), sprout::math::detail::as_float_compute(a));
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		d_sigmoid(IntType x) {
			return sprout::math::d_sigmoid(static_cast<double>(x));
		}
		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		d_sigmoid(ArithmeticType1 x, ArithmeticType2 a) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::d_sigmoid(static_cast<type>(x), static_cast<type>(a));
		}

		//
		// d2_sigmoid
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d2_sigmoid_impl_1(T s){
				return s * (1 - s) * (1 - 2 * s);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d2_sigmoid_impl_1(T s, T a){
				return a * a * s * (1 - s) * (1 - 2 * s);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d2_sigmoid_impl(T x){
				return sprout::math::detail::d2_sigmoid_impl_1(sprout::math::sigmoid(x));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			d2_sigmoid_impl(T x, T a){
				return sprout::math::detail::d2_sigmoid_impl_1(sprout::math::sigmoid(x, a), a);
			}
		}	// namespace detail
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		d2_sigmoid(FloatType x){
			return sprout::math::detail::d2_sigmoid_impl(sprout::math::detail::as_float_compute(x));
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		d2_sigmoid(FloatType x, FloatType a){
			return sprout::math::detail::d2_sigmoid_impl(sprout::math::detail::as_float_compute(x), sprout::math::detail::as_float_compute(a));
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		d2_sigmoid(IntType x) {
			return sprout::math::d2_sigmoid(static_cast<double>(x));
		}
		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		d2_sigmoid(ArithmeticType1 x, ArithmeticType2 a) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::d2_sigmoid(static_cast<type>(x), static_cast<type>(a));
		}
	}	// namespace math

	using sprout::math::sigmoid;
	using sprout::math::d_sigmoid;
	using sprout::math::d2_sigmoid;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIGMOID_HPP
