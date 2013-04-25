#ifndef SPROUT_MATH_COSH_HPP
#define SPROUT_MATH_COSH_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosh_impl_1(T x2, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::detail::pow_n(x2, n) / sprout::math::unchecked_factorial<T>(2 * n)
					: sprout::math::detail::cosh_impl_1(x2, n, n + (last - n) / 2)
						+ sprout::math::detail::cosh_impl_1(x2, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cosh_impl(T x) {
				return T(1) + sprout::math::detail::cosh_impl_1(
					x * x,
					1, sprout::math::factorial_limit<T>() / 2 + 1
					);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			cosh(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity()
					|| x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::cosh(x)
#else
					: x == 0 ? FloatType(1)
					: static_cast<FloatType>(sprout::math::detail::cosh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cosh(IntType x) {
				return sprout::math::detail::cosh(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::cosh;
	}	// namespace math

	using sprout::math::cosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COSH_HPP
