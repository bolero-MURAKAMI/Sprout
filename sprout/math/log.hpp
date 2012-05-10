#ifndef SPROUT_MATH_LOG_HPP
#define SPROUT_MATH_LOG_HPP

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
			log_impl_2(T x, T tmp, std::size_t n, T xn) {
				return n > sprout::math::factorial_limit<T>() ? tmp
					: sprout::math::detail::log_impl_2(
						x,
						tmp + (n % 2 ? 1 : -1) * xn / n,
						n + 1,
						xn * x
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_impl_1(T x) {
				return sprout::math::detail::log_impl_2(
					x,
					x,
					2,
					x * x
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_impl(T x) {
				return !(x > sprout::math::root_two<T>()) ? sprout::math::detail::log_impl_1(x - 1)
					: 2 * sprout::math::detail::log_impl(sprout::math::sqrt(x))
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log(FloatType x) {
				typedef double type;
				return x == 0 ? std::numeric_limits<FloatType>::quiet_NaN()
					: !(x > 0) ? -std::numeric_limits<FloatType>::infinity()
					: static_cast<FloatType>(sprout::math::detail::log_impl(x))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log(IntType x) {
				return sprout::math::detail::log(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::log;
#	else
		using sprout::math::detail::log;
#	endif
	}	// namespace math

	using sprout::math::log;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG_HPP
