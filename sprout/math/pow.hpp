#ifndef SPROUT_MATH_POW_HPP
#define SPROUT_MATH_POW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
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
			pow(FloatType x, FloatType y) {
				return x == 0 && y > 0 ? FloatType(0)
					: sprout::math::exp(y * sprout::math::log(x))
					;
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::math::float_promote<ArithmeticType1, ArithmeticType2>::type
			pow(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::math::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::pow(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::pow;
#	else
		using sprout::math::detail::pow;
#	endif
	}	// namespace math

	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_POW_HPP
