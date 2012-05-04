#ifndef SPROUT_MATH_EXPM1_HPP
#define SPROUT_MATH_EXPM1_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/exp.hpp>
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
			expm1(FloatType x) {
				return sprout::math::detail::exp(x) - 1;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			expm1(IntType x) {
				return sprout::math::detail::expm1(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::expm1;
#	else
		using sprout::math::detail::expm1;
#	endif
	}	// namespace math

	using sprout::math::expm1;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXPM1_HPP
