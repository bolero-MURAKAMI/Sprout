#ifndef SPROUT_MATH_ISFINITE_HPP
#define SPROUT_MATH_ISFINITE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
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
			isfinite(FloatType x) {
				return !sprout::math::isnan(x)
					&& !sprout::math::isinf(x)
					;
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::isfinite;
#	else
		using sprout::math::detail::isfinite;
#	endif
	}	// namespace math

	using sprout::math::isfinite;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISFINITE_HPP
