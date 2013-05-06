#ifndef SPROUT_MATH_ROUND_HPP
#define SPROUT_MATH_ROUND_HPP

#include <cstdint>
#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			round_impl_positive(T x, T x0) {
				return x - x0 < T(0.5) ? x0
					: x0 + T(1)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			round_impl_nagative(T x, T x0) {
				return x0 - x < T(0.5) ? x0
					: x0 - T(1)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			round_impl(T x) {
				return x < 0 ? sprout::math::detail::round_impl_nagative(x, -static_cast<T>(static_cast<std::uintmax_t>(-x)))
					: sprout::math::detail::round_impl_positive(x, static_cast<T>(static_cast<std::uintmax_t>(x)))
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			round(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::round(x)
#else
					: x == 0 ? x
					: std::numeric_limits<std::uintmax_t>::max() < x || std::numeric_limits<std::uintmax_t>::max() < -x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("round: large float rounding."), x)
					: static_cast<FloatType>(sprout::math::detail::round_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			round(IntType x) {
				return sprout::math::detail::round(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::round;
	}	// namespace math

	using sprout::math::round;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ROUND_HPP
