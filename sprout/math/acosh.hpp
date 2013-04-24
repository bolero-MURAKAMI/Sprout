#ifndef SPROUT_MATH_ACOSH_HPP
#define SPROUT_MATH_ACOSH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			acosh_impl(T x) {
				return sprout::math::log(x + sprout::math::sqrt(x * x - 1));
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			acosh(FloatType x) {
				return x < 1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::acosh(x)
#else
					: x == 1 ? FloatType(0)
					: static_cast<FloatType>(sprout::math::detail::acosh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			acosh(IntType x) {
				return sprout::math::detail::acosh(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// acosh
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		acosh(ArithmeticType x) {
			return sprout::math::detail::acosh(x);
		}
	}	// namespace math

	using sprout::math::acosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOSH_HPP
