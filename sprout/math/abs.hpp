#ifndef SPROUT_MATH_ABS_HPP
#define SPROUT_MATH_ABS_HPP

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
			inline SPROUT_CONSTEXPR FloatType
			abs(FloatType x) {
				return x < 0 ? -x : x;
			}
		}	// namespace detail

		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		abs(FloatType x) {
#		if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			using std::abs;
#		else
			using sprout::math::detail::abs;
#		endif
			return abs(x);
		}
	}	// namespace math

	using sprout::math::abs;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ABS_HPP
