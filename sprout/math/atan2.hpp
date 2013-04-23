#ifndef SPROUT_MATH_ATAN2_HPP
#define SPROUT_MATH_ATAN2_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/atan.hpp>
#include <sprout/math/constants.hpp>
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
			atan2(FloatType y, FloatType x) {
				return y == 0
						? x == 0 ? FloatType(0)
							: x < 0 ? sprout::math::pi<FloatType>()
							: FloatType(0)
					: x == 0 ? (y < 0 ? -1 : 1) * sprout::math::half_pi<FloatType>()
					: x == -std::numeric_limits<FloatType>::infinity()
						? y == std::numeric_limits<FloatType>::infinity() ? sprout::math::three_quarters_pi<FloatType>()
							: y == -std::numeric_limits<FloatType>::infinity() ? -sprout::math::three_quarters_pi<FloatType>()
							: (y < 0 ? -1 : 1) * sprout::math::half_pi<FloatType>()
					: x == std::numeric_limits<FloatType>::infinity()
						? y == std::numeric_limits<FloatType>::infinity() ? sprout::math::quarter_pi<FloatType>()
							: y == -std::numeric_limits<FloatType>::infinity() ? -sprout::math::quarter_pi<FloatType>()
							: FloatType(0)
					: y == std::numeric_limits<FloatType>::infinity() ? sprout::math::half_pi<FloatType>()
					: y == -std::numeric_limits<FloatType>::infinity() ? -sprout::math::half_pi<FloatType>()
					: x < 0 ? sprout::atan(y / x) + (y < 0 ? -1 : 1) * sprout::math::pi<FloatType>()
					: sprout::atan(y / x)
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
			atan2(ArithmeticType1 y, ArithmeticType2 x) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::atan2(static_cast<type>(y), static_cast<type>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::atan2;
	}	// namespace math

	using sprout::math::atan2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATAN2_HPP
