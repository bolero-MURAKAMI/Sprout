#ifndef SPROUT_MATH_LROUND_HPP
#define SPROUT_MATH_LROUND_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iround.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long
			lround(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? std::numeric_limits<long>::min()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::lround(x)
#else
					: sprout::math::iround<long>(x);
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long
			lround(IntType x) {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				return std::lround(x);
#else
				return sprout::math::iround<long>(x);
#endif
			}
		}	// namespace detail

		using sprout::math::detail::lround;
	}	// namespace math

	using sprout::math::lround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LROUND_HPP
