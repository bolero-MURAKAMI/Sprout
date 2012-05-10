#ifndef SPROUT_MATH_SIN_HPP
#define SPROUT_MATH_SIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/constants.hpp>
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
			sin(FloatType x) {
				return -sprout::math::cos(x + sprout::math::half_pi<FloatType>());
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::sin;
#	else
		using sprout::math::detail::sin;
#	endif
	}	// namespace math

	using sprout::math::sin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIN_HPP
