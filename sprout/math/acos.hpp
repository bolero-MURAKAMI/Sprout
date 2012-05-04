#ifndef SPROUT_MATH_ACOS_HPP
#define SPROUT_MATH_ACOS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/asin.hpp>
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
			acos(FloatType x) {
				return sprout::math::half_pi<FloatType>() - sprout::math::detail::asin(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			acos(IntType x) {
				return sprout::math::detail::acos(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::acos;
#	else
		using sprout::math::detail::acos;
#	endif
	}	// namespace math

	using sprout::math::acos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOS_HPP
