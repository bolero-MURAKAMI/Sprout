#ifndef SPROUT_MATH_ACOSH_HPP
#define SPROUT_MATH_ACOSH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			acosh(FloatType x) {
				return x == 1 ? FloatType(0)
					: x < 1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: sprout::log(x + sprout::sqrt(x * x - 1))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			acosh(IntType x) {
				return sprout::math::detail::acosh(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::acosh;
	}	// namespace math

	using sprout::math::acosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOSH_HPP
