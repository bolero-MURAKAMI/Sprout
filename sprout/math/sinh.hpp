#ifndef SPROUT_MATH_SINH_HPP
#define SPROUT_MATH_SINH_HPP

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
			sinh_impl(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::detail::pow_n(x, 2 * n + 1) / sprout::math::factorial<T>(2 * n + 1)
					: sprout::math::detail::sinh_impl(x, n, n + (last - n) / 2)
						+ sprout::math::detail::sinh_impl(x, n + (last - n) / 2, last)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sinh(FloatType x) {
				typedef typename sprout::math::detail::float_compute<FloatType>::type type;
				return x == 0 ? FloatType(1)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
					: static_cast<FloatType>(
						static_cast<type>(x) + sprout::math::detail::sinh_impl(
							static_cast<type>(x),
							1, (sprout::math::factorial_limit<type>() - 1) / 2 + 1
							)
						)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			sinh(IntType x) {
				return sprout::math::detail::sinh(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::sinh;
	}	// namespace math

	using sprout::math::sinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SINH_HPP
