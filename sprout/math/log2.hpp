#ifndef SPROUT_MATH_LOG2_HPP
#define SPROUT_MATH_LOG2_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log2_impl(T x) {
				return sprout::math::log(x) / sprout::math::ln_two<T>();
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log2(FloatType x) {
				return x == 0 ? -std::numeric_limits<FloatType>::infinity()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x < 0 ? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::log2(x)
#else
					: x == 1 ? FloatType(0)
					: static_cast<FloatType>(sprout::math::detail::log2_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log2(IntType x) {
				return sprout::math::detail::log2(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// log2
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		log2(ArithmeticType x) {
			return sprout::math::detail::log2(x);
		}
	}	// namespace math

	using sprout::math::log2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG2_HPP
