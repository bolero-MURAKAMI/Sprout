#ifndef SPROUT_MATH_ASIN_HPP
#define SPROUT_MATH_ASIN_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::math::unchecked_factorial<T>(2 * n)
						/ sprout::detail::pow_n(T(4), n) / sprout::detail::pow2(sprout::math::unchecked_factorial<T>(n)) / (2 * n + 1)
						* sprout::detail::pow_n(x, 2 * n + 1)
					: sprout::math::detail::asin_impl_1(x, n, n + (last - n) / 2)
						+ sprout::math::detail::asin_impl_1(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl(T x) {
				return x > sprout::math::half_root_two<T>()
					? sprout::math::half_pi<T>() - sprout::math::detail::asin_impl_1(sprout::math::sqrt(1 - x * x), 0, sprout::math::factorial_limit<T>() / 2 + 1)
					: x + sprout::math::detail::asin_impl_1(x, 1, sprout::math::factorial_limit<T>() / 2 + 1)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			asin(FloatType x) {
				return sprout::math::fabs(x) > 1 ? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::asin(x)
#else
					: x == 0 ? x
					: static_cast<FloatType>(
						x < 0 ? -sprout::math::detail::asin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(-x))
							: sprout::math::detail::asin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x))
						)
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			asin(IntType x) {
				return sprout::math::detail::asin(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::asin;
	}	// namespace math

	using sprout::math::asin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASIN_HPP
