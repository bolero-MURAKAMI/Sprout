#ifndef SPROUT_MATH_SINH_HPP
#define SPROUT_MATH_SINH_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinh_impl(T x, T tmp, std::size_t n, T x2n1) {
				return 2 * n + 1 > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::sinh_impl(
						x,
						tmp + x2n1 / sprout::math::factorial<T>(2 * n + 1),
						n + 1,
						x2n1 * x * x
						)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sinh(FloatType x) {
				typedef double type;
				return static_cast<FloatType>(sprout::math::detail::sinh_impl(
					static_cast<type>(x),
					static_cast<type>(x),
					1,
					static_cast<type>(x) * static_cast<type>(x) * static_cast<type>(x)
					));
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::sinh;
#	else
		using sprout::math::detail::sinh;
#	endif
	}	// namespace math

	using sprout::math::sinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SINH_HPP
