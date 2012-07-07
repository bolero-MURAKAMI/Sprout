#ifndef SPROUT_MATH_HYPOT_HPP
#define SPROUT_MATH_HYPOT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/sqrt.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			hypot(FloatType x, FloatType y) {
				return sprout::math::sqrt(x * x + y * y);
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
			hypot(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::hypot(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::hypot;
	}	// namespace math

	using sprout::math::hypot;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_HYPOT_HPP
