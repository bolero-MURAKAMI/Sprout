#ifndef SPROUT_MATH_FMAX_HPP
#define SPROUT_MATH_FMAX_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			fmax(FloatType x, FloatType y) {
				return sprout::math::isnan(y) ? x
					: sprout::math::isnan(x) ? y
					: y == -std::numeric_limits<FloatType>::infinity() ? x
					: x == std::numeric_limits<FloatType>::infinity() ? x
					: x == -std::numeric_limits<FloatType>::infinity() ? y
					: y == std::numeric_limits<FloatType>::infinity() ? y
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: x == 0 && y == 0 ? x
					: std::fmax(x, y)
#else
					: x < y ? y : x
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
			fmax(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::fmax(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::fmax;
	}	// namespace math

	using sprout::math::fmax;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMAX_HPP
