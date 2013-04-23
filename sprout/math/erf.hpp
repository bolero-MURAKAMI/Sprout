#ifndef SPROUT_MATH_ERF_HPP
#define SPROUT_MATH_ERF_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? (n % 2 ? -1 : 1) / sprout::math::factorial<T>(n) / (2 * n + 1) * sprout::detail::pow_n(x, 2 * n + 1)
					: sprout::math::detail::erf_impl_1(x, n, n + (last - n) / 2)
						+ sprout::math::detail::erf_impl_1(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl(T x) {
				return sprout::math::two_div_root_pi<T>()
					* (x + sprout::math::detail::erf_impl_1(x, 1, sprout::math::factorial_limit<T>() + 1))
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl(T x2, T a) {
				return T(1) - sprout::exp(-x2 / (T(1) + a * x2) * (sprout::math::quarter_pi<T>() + a * x2));
			}
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			erf(FloatType x) {
				typedef typename sprout::math::detail::float_compute<FloatType>::type type;
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? FloatType(1)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(-1)
					: static_cast<FloatType>(sprout::math::detail::erf_impl(static_cast<type>(x)))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			erf(IntType x) {
				return sprout::math::detail::erf(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::erf;
	}	// namespace math

	using sprout::math::erf;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ERF_HPP
