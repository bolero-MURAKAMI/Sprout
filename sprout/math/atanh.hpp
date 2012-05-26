#ifndef SPROUT_MATH_ATANH_HPP
#define SPROUT_MATH_ATANH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/log.hpp>
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
			atanh(FloatType x) {
				return x < -1 || x > 1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x == -1 ? -std::numeric_limits<FloatType>::infinity()
					: x == 1 ? std::numeric_limits<FloatType>::infinity()
					: sprout::math::log((1 + x) / (1 - x)) / 2
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			atanh(IntType x) {
				return sprout::math::detail::atanh(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::atanh;
#	else
		using sprout::math::detail::atanh;
#	endif
	}	// namespace math

	using sprout::math::atanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATANH_HPP
