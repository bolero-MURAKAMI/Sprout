#ifndef SPROUT_MATH_EXP_HPP
#define SPROUT_MATH_EXP_HPP

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
			exp_impl(T x, T tmp, std::size_t n, T xn) {
				return n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::exp_impl(
						x,
						tmp + xn / sprout::math::factorial<T>(n),
						n + 1,
						xn * x
						)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			exp(FloatType x) {
				typedef double type;
				return static_cast<FloatType>(sprout::math::detail::exp_impl(
					static_cast<type>(x),
					type(1),
					1,
					static_cast<type>(x)
					));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			exp(IntType x) {
				return sprout::math::detail::exp(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::exp;
#	else
		using sprout::math::detail::exp;
#	endif
	}	// namespace math

	using sprout::math::exp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP_HPP
