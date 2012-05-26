#ifndef SPROUT_MATH_FMAX_HPP
#define SPROUT_MATH_FMAX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			fmax(FloatType x, FloatType y) {
				return x < y ? y : x;
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::math::float_promote<ArithmeticType1, ArithmeticType2>::type
			fmax(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::math::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::fmax(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::fmax;
#	else
		using sprout::math::detail::fmax;
#	endif
	}	// namespace math

	using sprout::math::fmax;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMAX_HPP
