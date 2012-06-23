#ifndef SPROUT_MATH_COS_HPP
#define SPROUT_MATH_COS_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cos_impl(T x, T tmp, std::size_t n, T x2n) {
				return 2 * n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::cos_impl(
						x,
						tmp + (n % 2 ? -1 : 1) * x2n / sprout::math::factorial<T>(2 * n),
						n + 1,
						x2n * x * x
						)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			cos(FloatType x) {
				typedef double type;
				return x == std::numeric_limits<FloatType>::infinity()
					|| x == -std::numeric_limits<FloatType>::infinity()
					? std::numeric_limits<FloatType>::quiet_NaN()
					: static_cast<FloatType>(sprout::math::detail::cos_impl(
						static_cast<type>(x),
						type(1),
						1,
						static_cast<type>(x) * static_cast<type>(x)
						))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cos(IntType x) {
				return sprout::math::detail::cos(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::cos;
	}	// namespace math

	using sprout::math::cos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COS_HPP
