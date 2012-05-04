#ifndef SPROUT_MATH_EXP2_HPP
#define SPROUT_MATH_EXP2_HPP

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
			exp2(FloatType x) {
				return sprout::math::detail::exp(x * sprout::math::ln_two<FloatType>());
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			exp2(IntType x) {
				return sprout::math::detail::exp2(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::exp2;
#	else
		using sprout::math::detail::exp2;
#	endif
	}	// namespace math

	using sprout::math::exp2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP2_HPP
