#ifndef SPROUT_MATH_POW_HPP
#define SPROUT_MATH_POW_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/log.hpp>
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
			pow(FloatType x, FloatType y) {
				return x == 0
						? y < 0 ? std::numeric_limits<FloatType>::infinity()
						: y > 0 ? FloatType(0)
						: sprout::exp(y * sprout::log(x))
					: x == -1 && (y == std::numeric_limits<FloatType>::infinity() || y == -std::numeric_limits<FloatType>::infinity()) ? FloatType(1)
					: x == 1 ? FloatType(1)
					: y == 0 ? FloatType(1)
					: y == -std::numeric_limits<FloatType>::infinity()
						? x < 1 && x > -1 ? std::numeric_limits<FloatType>::infinity()
						: x > 1 || x < -1 ? FloatType(0)
						: sprout::exp(y * sprout::log(x))
					: y == std::numeric_limits<FloatType>::infinity()
						? x < 1 && x > -1 ? FloatType(0)
						: x > 1 || x < -1 ? std::numeric_limits<FloatType>::infinity()
						: sprout::exp(y * sprout::log(x))
					: x == -std::numeric_limits<FloatType>::infinity()
						? y < 0 ? FloatType(0)
						: y > 0 ? std::numeric_limits<FloatType>::infinity()
						: sprout::exp(y * sprout::log(x))
					: x == std::numeric_limits<FloatType>::infinity()
						? y < 0 ? FloatType(0)
						: y > 0 ? std::numeric_limits<FloatType>::infinity()
						: sprout::exp(y * sprout::log(x))
					: sprout::exp(y * sprout::log(x))
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
			pow(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::pow(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::pow;
	}	// namespace math

	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_POW_HPP
