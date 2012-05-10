#ifndef SPROUT_MATH_ISNAN_HPP
#define SPROUT_MATH_ISNAN_HPP

#include <type_traits>
#include <sprout/config.hpp>
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
			inline SPROUT_CONSTEXPR int
			isnan(FloatType x) {
				return !(x == x);
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::isnan;
#	else
		using sprout::math::detail::isnan;
#	endif
	}	// namespace math

	using sprout::math::isnan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISNAN_HPP
