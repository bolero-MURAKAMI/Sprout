#ifndef SPROUT_MATH_ISSUBNORMAL_HPP
#define SPROUT_MATH_ISSUBNORMAL_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/iszero.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			issubnormal_or_zero(FloatType x) {
				return x > 0
					? x < std::numeric_limits<double>::min()
					: x > -std::numeric_limits<double>::min()
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			issubnormal(FloatType x) {
				return !sprout::math::iszero(x)
					&& sprout::math::detail::issubnormal_or_zero(x)
					;
			}
		}	// namespace detail

		using sprout::math::detail::issubnormal;
	}	// namespace math

	using sprout::math::issubnormal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISSUBNORMAL_HPP
