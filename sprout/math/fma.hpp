#ifndef SPROUT_MATH_FMA_HPP
#define SPROUT_MATH_FMA_HPP

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
			fma(FloatType x, FloatType y, FloatType z) {
				return x * y + z;
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename ArithmeticType3,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value
						&& std::is_arithmetic<ArithmeticType2>::value
						&& std::is_arithmetic<ArithmeticType3>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::math::float_promote<
				ArithmeticType1, ArithmeticType2, ArithmeticType3
			>::type
			fma(ArithmeticType1 x, ArithmeticType2 y, ArithmeticType3 z) {
				typedef typename sprout::math::float_promote<
					ArithmeticType1, ArithmeticType2, ArithmeticType3
				>::type type;
				return sprout::math::detail::fma(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::fma;
#	else
		using sprout::math::detail::fma;
#	endif
	}	// namespace math

	using sprout::math::fma;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMA_HPP
