#ifndef SPROUT_MATH_ISINF_HPP
#define SPROUT_MATH_ISINF_HPP

#include <limits>
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
			isinf(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity()
					|| x == -std::numeric_limits<FloatType>::infinity()
					;
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::isinf;
#	else
		using sprout::math::detail::isinf;
#	endif
	}	// namespace math

	using sprout::math::isinf;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISINF_HPP
