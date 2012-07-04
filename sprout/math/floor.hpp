#ifndef SPROUT_MATH_FLOOR_HPP
#define SPROUT_MATH_FLOOR_HPP

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
			floor_impl(FloatType x, FloatType x0) {
				return x0 - x < std::numeric_limits<FloatType>::epsilon() ? x0
					: x0 - 1
					;
			}
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			floor(FloatType x) {
				return sprout::math::isinf(x) ? x
					: std::numeric_limits<std::uintmax_t>::max() < x || std::numeric_limits<std::uintmax_t>::max() < -x
						? throw std::domain_error("floor: Sorry, not implemented.")
					: x < 0 ? sprout::math::detail::floor_impl(x, -static_cast<FloatType>(static_cast<std::uintmax_t>(-x)))
					: static_cast<FloatType>(static_cast<std::uintmax_t>(x))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			floor(IntType x) {
				return sprout::math::detail::floor(static_cast<double>(x));
			}
		}	// namespacedetailmath

		using NS_SPROUT_MATH_DETAIL::floor;
	}	// namespace math

	using sprout::math::floor;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOOR_HPP
