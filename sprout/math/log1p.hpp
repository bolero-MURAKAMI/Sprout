#ifndef SPROUT_MATH_LOG1P_HPP
#define SPROUT_MATH_LOG1P_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/log.hpp>
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
			log1p(FloatType x) {
				return sprout::math::log(1 + x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log1p(IntType x) {
				return sprout::math::detail::log1p(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::log1p;
#	else
		using sprout::math::detail::log1p;
#	endif
	}	// namespace math

	using sprout::math::log1p;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG1P_HPP
