#ifndef SPROUT_MATH_ISNORMAL_HPP
#define SPROUT_MATH_ISNORMAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/issubnormal.hpp>
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
			isnormal(FloatType x) {
				return !sprout::math::isnan(x)
					&& !sprout::math::isinf(x)
					&& !sprout::math::detail::issubnormal_or_zero(x)
					;
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::isnormal;
#	else
		using sprout::math::detail::isnormal;
#	endif
	}	// namespace math

	using sprout::math::isnormal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISNORMAL_HPP
