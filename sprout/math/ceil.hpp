#ifndef SPROUT_MATH_CEIL_HPP
#define SPROUT_MATH_CEIL_HPP

#include <cstdint>
#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			ceil_impl_1(T x, T x0) {
				return sprout::math::equal_to(x, x0) ? x0
					: x0 + T(1)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			ceil_impl(T x) {
				return x < 0 ? -static_cast<T>(static_cast<std::uintmax_t>(-x))
					: sprout::math::detail::ceil_impl_1(x, static_cast<T>(static_cast<std::uintmax_t>(x)))
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			ceil(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::ceil(x)
#else
					: x == 0 ? x
					: std::numeric_limits<std::uintmax_t>::max() < x || std::numeric_limits<std::uintmax_t>::max() < -x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("ceil: large float rounding."), x)
					: static_cast<FloatType>(sprout::math::detail::ceil_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			ceil(IntType x) {
				return sprout::math::detail::ceil(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::ceil;
	}	// namespace math

	using sprout::math::ceil;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CEIL_HPP
