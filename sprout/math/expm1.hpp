#ifndef SPROUT_MATH_EXPM1_HPP
#define SPROUT_MATH_EXPM1_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			expm1_impl(T x) {
				return sprout::math::exp(x) - T(1);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			expm1(FloatType x) {
				return x == -std::numeric_limits<FloatType>::infinity() ? FloatType(-1)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::expm1(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::expm1_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			expm1(IntType x) {
				return sprout::math::detail::expm1(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// expm1
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		expm1(ArithmeticType x) {
			return sprout::math::detail::expm1(x);
		}
	}	// namespace math

	using sprout::math::expm1;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXPM1_HPP
