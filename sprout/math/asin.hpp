#ifndef SPROUT_MATH_ASIN_HPP
#define SPROUT_MATH_ASIN_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_2(T x, T tmp, std::size_t n, T x2n1, T _4n) {
				return 2 * n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::asin_impl_2(
						x,
						tmp + sprout::math::factorial<T>(2 * n)
							/ _4n / sprout::math::factorial<T>(n) / sprout::math::factorial<T>(n) / (2 * n + 1)
							* x2n1
							,
						n + 1,
						x2n1 * x * x,
						_4n * 4
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl_1(T x) {
				return sprout::math::detail::asin_impl_2(
					x,
					x,
					1,
					x * x * x,
					T(4)
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asin_impl(T x) {
				return x > sprout::math::half_root_two<T>()
						? sprout::math::half_pi<T>() - sprout::math::detail::asin_impl_1(sprout::math::detail::sqrt(1 - x * x))
					: sprout::math::detail::asin_impl_1(x)
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

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::asin;
#	else
		using sprout::math::detail::asin;
#	endif
	}	// namespace math

	using sprout::math::asin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASIN_HPP
