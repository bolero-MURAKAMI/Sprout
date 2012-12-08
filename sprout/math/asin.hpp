#ifndef SPROUT_MATH_ASIN_HPP
#define SPROUT_MATH_ASIN_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::math::factorial<T>(2 * n)
						/ sprout::detail::pow_n(T(4), n) / sprout::detail::pow2(sprout::math::factorial<T>(n)) / (2 * n + 1)
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
				typedef double type;
				return x > 1 || x < -1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: x < 0 ? -static_cast<FloatType>(sprout::math::detail::asin_impl(static_cast<type>(-x)))
					: static_cast<FloatType>(sprout::math::detail::asin_impl(static_cast<type>(x)))
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

		using NS_SPROUT_MATH_DETAIL::asin;
	}	// namespace math

	using sprout::math::asin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASIN_HPP
