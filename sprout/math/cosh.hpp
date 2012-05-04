#ifndef SPROUT_MATH_COSH_HPP
#define SPROUT_MATH_COSH_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
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
			cosh_impl(T x, T tmp, std::size_t n, T x2n) {
				return 2 * n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::cosh_impl(
						x,
						tmp + 1 / sprout::math::factorial<T>(2 * n) * x2n,
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
			cosh(FloatType x) {
				typedef double type;
				return static_cast<FloatType>(sprout::math::detail::cosh_impl(
					static_cast<type>(x),
					type(1),
					1,
					static_cast<type>(x) * static_cast<type>(x)
					));
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::cosh;
#	else
		using sprout::math::detail::cosh;
#	endif
	}	// namespace math

	using sprout::math::cosh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COSH_HPP
