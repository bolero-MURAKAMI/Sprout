#ifndef SPROUT_MATH_TAN_HPP
#define SPROUT_MATH_TAN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
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
			tan(FloatType x) {
				return sprout::math::detail::sin(x) / sprout::math::detail::cos(x);
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::tan;
#	else
		using sprout::math::detail::tan;
#	endif
	}	// namespace math

	using sprout::math::tan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TAN_HPP
