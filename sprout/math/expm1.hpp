#ifndef SPROUT_MATH_EXPM1_HPP
#define SPROUT_MATH_EXPM1_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			expm1(FloatType x) {
				return x == 0 ? FloatType(0)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(-1)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: sprout::exp(x) - FloatType(1)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			expm1(IntType x) {
				return sprout::math::detail::expm1(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::expm1;
	}	// namespace math

	using sprout::math::expm1;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXPM1_HPP
