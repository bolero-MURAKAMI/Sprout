#ifndef SPROUT_MATH_ILOGB_HPP
#define SPROUT_MATH_ILOGB_HPP

#include <climits>
#include <cfloat>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/logb.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iszero.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			ilogb(FloatType x) {
				return sprout::math::iszero(x) ? FP_ILOGB0
					: sprout::math::isinf(x) ? INT_MAX
					: sprout::math::isnan(x) ? FP_ILOGBNAN
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::ilogb(x)
#else
					: static_cast<int>(sprout::math::logb(x))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			ilogb(IntType x) {
				return sprout::math::detail::ilogb(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::ilogb;
	}	// namespace math

	using sprout::math::ilogb;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ILOGB_HPP
