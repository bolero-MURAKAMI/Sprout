#ifndef SPROUT_MATH_ATANH_HPP
#define SPROUT_MATH_ATANH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			atanh_impl(T x) {
				return sprout::math::log((1 + x) / (1 - x)) / 2;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			atanh(FloatType x) {
				return x == 1 ? std::numeric_limits<FloatType>::infinity()
					: x == -1 ? -std::numeric_limits<FloatType>::infinity()
					: sprout::math::fabs(x) > 1 ? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::atanh(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::atanh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			atanh(IntType x) {
				return sprout::math::detail::atanh(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// atanh
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		atanh(ArithmeticType x) {
			return sprout::math::detail::atanh(x);
		}
	}	// namespace math

	using sprout::math::atanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATANH_HPP
