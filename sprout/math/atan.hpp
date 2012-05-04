#ifndef SPROUT_MATH_ATAN_HPP
#define SPROUT_MATH_ATAN_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan_impl_2(T x, T tmp, std::size_t n, T x2n1) {
				return n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::atan_impl_2(
						x,
						tmp + (n % 2 ? -1 : 1) * x2n1 / (2 * n + 1),
						n + 1,
						x2n1 * x * x
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan_impl_1(T x) {
				return sprout::math::detail::atan_impl_2(
					x,
					x,
					1,
					x * x * x
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			atan_impl(T x) {
				return x > sprout::math::root_two<T>() + 1
						? sprout::math::half_pi<T>() - sprout::math::detail::atan_impl_1(1 / x)
					: x > sprout::math::root_two<T>() - 1
						? sprout::math::quarter_pi<T>() + sprout::math::detail::atan_impl_1((x - 1) / (x + 1))
					: sprout::math::detail::atan_impl_1(x)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			atan(FloatType x) {
				typedef double type;
				return static_cast<FloatType>(
					x < 0 ? -sprout::math::detail::atan_impl(static_cast<type>(-x))
						: sprout::math::detail::atan_impl(static_cast<type>(x))
					);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			atan(IntType x) {
				return sprout::math::detail::atan(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::atan;
#	else
		using sprout::math::detail::atan;
#	endif
	}	// namespace math

	using sprout::math::atan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATAN_HPP
