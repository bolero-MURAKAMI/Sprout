#ifndef SPROUT_MATH_SIGNBIT_HPP
#define SPROUT_MATH_SIGNBIT_HPP

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
			inline SPROUT_CONSTEXPR int
			signbit(FloatType x) {
				return x < 0;
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::signbit;
#	else
		using sprout::math::detail::signbit;
#	endif
	}	// namespace math

	using sprout::math::signbit;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIGNBIT_HPP
