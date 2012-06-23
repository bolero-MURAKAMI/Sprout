#ifndef SPROUT_MATH_SQRT_HPP
#define SPROUT_MATH_SQRT_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sqrt_impl_1(T x, T s, T s2) {
				return !(s < s2) ? s2
					: sprout::math::detail::sqrt_impl_1(
						x,
						(x / s + s) / 2,
						s
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sqrt_impl(T x, T s) {
				return sprout::math::detail::sqrt_impl_1(
						x,
						(x / s + s) / 2,
						s
						)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sqrt(FloatType x) {
				typedef double type;
				return x < 0 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x == 0 ? type(0)
					: static_cast<FloatType>(sprout::math::detail::sqrt_impl(
						static_cast<type>(x),
						x > 1 ? static_cast<type>(x) : type(1)
						));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			sqrt(IntType x) {
				return sprout::math::detail::sqrt(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::sqrt;
	}	// namespace math

	using sprout::math::sqrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SQRT_HPP
