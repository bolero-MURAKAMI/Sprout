#ifndef SPROUT_MATH_TRUNC_HPP
#define SPROUT_MATH_TRUNC_HPP

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
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			trunc(FloatType x) {
				return sprout::math::isinf(x) ? x
					: std::numeric_limits<std::uintmax_t>::max() < x || std::numeric_limits<std::uintmax_t>::max() < -x
						? throw std::domain_error("trunc: Sorry, not implemented.")
					: x < 0 ? -static_cast<FloatType>(static_cast<std::uintmax_t>(-x))
					: static_cast<FloatType>(static_cast<std::uintmax_t>(x))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			trunc(IntType x) {
				return sprout::math::detail::trunc(static_cast<double>(x));
			}
		}	// namespacedetailmath

		using NS_SPROUT_MATH_DETAIL::trunc;
	}	// namespace math

	using sprout::math::trunc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TRUNC_HPP
