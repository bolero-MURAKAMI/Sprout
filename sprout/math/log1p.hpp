#ifndef SPROUT_MATH_LOG1P_HPP
#define SPROUT_MATH_LOG1P_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/log.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log1p_impl(T x) {
				return sprout::math::log(T(1) + x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log1p(FloatType x) {
				return x == -1 ? -std::numeric_limits<FloatType>::infinity()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x < -1 ? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::log1p(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::log1p_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log1p(IntType x) {
				return sprout::math::detail::log1p(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// log1p
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		log1p(ArithmeticType x) {
			return sprout::math::detail::log1p(x);
		}
	}	// namespace math

	using sprout::math::log1p;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG1P_HPP
