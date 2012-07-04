#ifndef SPROUT_MATH_LLROUND_HPP
#define SPROUT_MATH_LLROUND_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename FloatType>
			inline SPROUT_CONSTEXPR long long
			llround_impl_positive(FloatType x, long long x0) {
				return x - x0 < FloatType(0.5) ? x0
					: x0 + 1
					;
			}
			template<typename FloatType>
			inline SPROUT_CONSTEXPR long long
			llround_impl_nagative(FloatType x, long long x0) {
				return x0 - x < FloatType(0.5) ? x0
					: x0 - 1
					;
			}
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(FloatType x) {
				return x < 0 ? sprout::math::detail::llround_impl_nagative(x, static_cast<long long>(x))
					: sprout::math::detail::llround_impl_positive(x, static_cast<long long>(x))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(IntType x) {
				return static_cast<long long>(x);
			}
		}	// namespacedetailmath

		using NS_SPROUT_MATH_DETAIL::llround;
	}	// namespace math

	using sprout::math::llround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LLROUND_HPP
