#ifndef SPROUT_MATH_FABS_HPP
#define SPROUT_MATH_FABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
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
			fabs(FloatType x) {
				return x < 0 ? -x : x;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			fabs(IntType x) {
				return sprout::math::detail::fabs(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::fabs;
#	else
		using sprout::math::detail::fabs;
#	endif
	}	// namespace math

	using sprout::math::fabs;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FABS_HPP
