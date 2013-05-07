#ifndef SPROUT_MATH_FMA_HPP
#define SPROUT_MATH_FMA_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/signbit.hpp>
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
			fma(FloatType x, FloatType y, FloatType z) {
				return sprout::math::isnan(x) ? x
					: sprout::math::isnan(y) ? y
					: sprout::math::isnan(z) ? z
					: sprout::math::isinf(x) && y == 0 ? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::math::isinf(y) && x == 0 ? std::numeric_limits<FloatType>::quiet_NaN()
					: (sprout::math::isinf(x) || sprout::math::isinf(y)) && sprout::math::isinf(z) && (sprout::math::signbit(x) ^ sprout::math::signbit(y) ^ sprout::math::signbit(z))
						? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::fma(x, y, z)
#else
					: x * y + z
#endif
					;
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
			inline SPROUT_CONSTEXPR typename sprout::float_promote<
				ArithmeticType1, ArithmeticType2, ArithmeticType3
			>::type
			fma(ArithmeticType1 x, ArithmeticType2 y, ArithmeticType3 z) {
				typedef typename sprout::float_promote<
					ArithmeticType1, ArithmeticType2, ArithmeticType3
				>::type type;
				return sprout::math::detail::fma(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
			}
		}	// namespace detail

		using sprout::math::detail::fma;
	}	// namespace math

	using sprout::math::fma;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMA_HPP
