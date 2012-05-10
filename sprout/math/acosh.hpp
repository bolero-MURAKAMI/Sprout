#ifndef SPROUT_MATH_ACOSH_HPP
#define SPROUT_MATH_ACOSH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			acosh(FloatType x) {
				return x < 1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: sprout::math::log(x + sprout::math::sqrt(x * x - 1))
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::acosh;
#	else
		using sprout::math::detail::acosh;
#	endif
	}	// namespace math

	using sprout::math::acosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOSH_HPP
