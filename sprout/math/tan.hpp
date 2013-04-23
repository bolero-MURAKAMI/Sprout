#ifndef SPROUT_MATH_TAN_HPP
#define SPROUT_MATH_TAN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			tan(FloatType x) {
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::sin(x) / sprout::cos(x)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			tan(IntType x) {
				return sprout::math::detail::tan(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::tan;
	}	// namespace math

	using sprout::math::tan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TAN_HPP
