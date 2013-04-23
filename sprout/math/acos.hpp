#ifndef SPROUT_MATH_ACOS_HPP
#define SPROUT_MATH_ACOS_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/asin.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			acos_impl(T x) {
				return sprout::math::half_pi<T>() - sprout::math::asin(x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			acos(FloatType x) {
				return sprout::math::fabs(x) > 1 ? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::acos(x)
#else
					: x == 1 ? FloatType(0)
					: static_cast<FloatType>(sprout::math::detail::acos_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			acos(IntType x) {
				return sprout::math::detail::acos(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// acos
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		acos(ArithmeticType x) {
			return sprout::math::detail::acos(x);
		}
	}	// namespace math

	using sprout::math::acos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOS_HPP
