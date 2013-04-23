#ifndef SPROUT_MATH_SIN_HPP
#define SPROUT_MATH_SIN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/cos.hpp>
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
			sin(FloatType x) {
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::quiet_NaN()
					: -sprout::cos(x + sprout::math::half_pi<FloatType>())
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			sin(IntType x) {
				return sprout::math::detail::sin(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::sin;
	}	// namespace math

	using sprout::math::sin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIN_HPP
