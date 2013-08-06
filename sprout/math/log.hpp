#ifndef SPROUT_MATH_LOG_HPP
#define SPROUT_MATH_LOG_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_impl_2(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? (n % 2 ? 1 : -1) * sprout::detail::pow_n(x, n) / n
					: sprout::math::detail::log_impl_2(x, n, n + (last - n) / 2)
						+ sprout::math::detail::log_impl_2(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_impl_1(T x) {
				return !(x > sprout::math::root_two<T>())
					? sprout::math::detail::log_impl_2(x - T(1), 1, sprout::math::factorial_limit<T>() + 1)
					: T(2) * sprout::math::detail::log_impl_1(sprout::math::sqrt(x))
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			log_impl(T x) {
				return x < 1 ? -sprout::math::detail::log_impl_1(T(1) / x)
					: sprout::math::detail::log_impl_1(x)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == 0 ? -sprout::numeric_limits<FloatType>::infinity()
					: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
					: x < 0 ? sprout::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::log(x)
#else
					: x == 1 ? FloatType(0)
					: static_cast<FloatType>(sprout::math::detail::log_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
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

		using sprout::math::detail::log;
	}	// namespace math

	using sprout::math::log;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG_HPP
