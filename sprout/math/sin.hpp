#ifndef SPROUT_MATH_SIN_HPP
#define SPROUT_MATH_SIN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sin_impl(T x) {
				return -sprout::math::cos(x + sprout::math::half_pi<T>());
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sin(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity()
					|| x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::sin(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::sin_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			sin(IntType x) {
				return sprout::math::detail::sin(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::sin;
	}	// namespace math

	using sprout::math::sin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIN_HPP
