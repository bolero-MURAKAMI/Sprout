#ifndef SPROUT_MATH_FMOD_HPP
#define SPROUT_MATH_FMOD_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/trunc.hpp>
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
			fmod(FloatType x, FloatType y) {
				return y == 0 ? throw std::domain_error("fmod: divide by zero.")
					: x - sprout::math::trunc(x / y) * y
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
			fmod(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::fmod(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::fmod;
	}	// namespace math

	using sprout::math::fmod;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMOD_HPP
