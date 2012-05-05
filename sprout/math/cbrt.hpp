#ifndef SPROUT_MATH_CBRT_HPP
#define SPROUT_MATH_CBRT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/pow.hpp>
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
			cbrt(FloatType x) {
				return x < 0 ? -sprout::math::detail::pow(-x, sprout::math::third<FloatType>())
					: sprout::math::detail::pow(x, sprout::math::third<FloatType>())
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cbrt(IntType x) {
				return sprout::math::detail::cbrt(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::cbrt;
#	else
		using sprout::math::detail::cbrt;
#	endif
	}	// namespace math

	using sprout::math::cbrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CBRT_HPP
