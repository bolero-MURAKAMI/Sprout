#ifndef SPROUT_MATH_TANH_HPP
#define SPROUT_MATH_TANH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/sinh.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			tanh_impl(T x) {
				return sprout::math::sinh(x) / sprout::math::cosh(x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			tanh(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity() ? FloatType(1)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(-1)
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::tanh(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::tanh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			tanh(IntType x) {
				return sprout::math::detail::tanh(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::tanh;
	}	// namespace math

	using sprout::math::tanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TANH_HPP
