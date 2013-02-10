#ifndef SPROUT_MATH_REMAINDER_HPP
#define SPROUT_MATH_REMAINDER_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/round.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			remainder(FloatType x, FloatType y) {
				return y == 0 ? throw std::domain_error("remainder: divide by zero.")
					: x - sprout::math::round(x / y) * y
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
