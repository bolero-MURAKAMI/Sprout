#ifndef SPROUT_MATH_ROUND_HPP
#define SPROUT_MATH_ROUND_HPP

#include <cstdint>
#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename FloatType>
			inline SPROUT_CONSTEXPR FloatType
			round_impl_positive(FloatType x, FloatType x0) {
				return x - x0 < FloatType(0.5) ? x0
					: x0 + 1
					;
			}
			template<typename FloatType>
			inline SPROUT_CONSTEXPR FloatType
			round_impl_nagative(FloatType x, FloatType x0) {
				return x0 - x < FloatType(0.5) ? x0
					: x0 - 1
					;
			}
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			round(FloatType x) {
				return sprout::math::isinf(x) ? x
					: std::numeric_limits<std::uintmax_t>::max() < x || std::numeric_limits<std::uintmax_t>::max() < -x
						? SPROUT_MATH_DETAIL_INT_CONVERSION_OVERFLOW(std::domain_error("round: Sorry, not implemented."), x)
					: x < 0 ? sprout::math::detail::round_impl_nagative(x, -static_cast<FloatType>(static_cast<std::uintmax_t>(-x)))
					: sprout::math::detail::round_impl_positive(x, static_cast<FloatType>(static_cast<std::uintmax_t>(x)))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			round(IntType x) {
				return sprout::math::detail::round(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::round;
	}	// namespace math

	using sprout::math::round;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ROUND_HPP
