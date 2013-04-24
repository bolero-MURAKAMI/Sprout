#ifndef SPROUT_MATH_EXP2_HPP
#define SPROUT_MATH_EXP2_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp2_impl(T x) {
				return sprout::math::exp(x * sprout::math::ln_two<T>());
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			exp2(FloatType x) {
				return x == -std::numeric_limits<FloatType>::infinity() ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::exp2(x)
#else
					: x == 0 ? FloatType(1)
					: static_cast<FloatType>(sprout::math::detail::exp2_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			exp2(IntType x) {
				return sprout::math::detail::exp2(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// exp2
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		exp2(ArithmeticType x) {
			return sprout::math::detail::exp2(x);
		}
	}	// namespace math

	using sprout::math::exp2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP2_HPP
