#ifndef SPROUT_MATH_REMAINDER_HPP
#define SPROUT_MATH_REMAINDER_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/round.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			remainder_impl(T x, T y) {
				return x - sprout::math::round(x / y) * y;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			remainder(FloatType x, FloatType y) {
				return sprout::math::isnan(y)
						? sprout::math::isnan(x)
							? sprout::math::signbit(y) || sprout::math::signbit(x) ? -std::numeric_limits<FloatType>::quiet_NaN()
								: std::numeric_limits<FloatType>::quiet_NaN()
							: y
					: sprout::math::isnan(x) ? x
					: x == 0 && y != 0 ? x
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity() || y == 0
						? std::numeric_limits<FloatType>::quiet_NaN()
					: y == std::numeric_limits<FloatType>::infinity() || y == -std::numeric_limits<FloatType>::infinity() ? x
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::remainder(x, y)
#else
					: static_cast<FloatType>(sprout::math::detail::remainder_impl(
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y)
						))
#endif
					;
			}
			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
			remainder(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::remainder(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::remainder;
	}	// namespace math

	using sprout::math::remainder;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_REMAINDER_HPP
