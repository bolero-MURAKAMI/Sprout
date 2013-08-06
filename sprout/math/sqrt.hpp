#ifndef SPROUT_MATH_SQRT_HPP
#define SPROUT_MATH_SQRT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sqrt_impl_2(T x, T s, T s2) {
				return !(s < s2) ? s2
					: sprout::math::detail::sqrt_impl_2(x, (x / s + s) / 2, s)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sqrt_impl_1(T x, T s) {
				return sprout::math::detail::sqrt_impl_2(x, (x / s + s) / 2, s);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sqrt_impl(T x) {
				return sprout::math::detail::sqrt_impl_1(x, x > 1 ? x : T(1));
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sqrt(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
					: x < 0 ? -sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::sqrt(x)
#else
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::sqrt_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
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

		using sprout::math::detail::sqrt;
	}	// namespace math

	using sprout::math::sqrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SQRT_HPP
