#ifndef SPROUT_MATH_ASINH_HPP
#define SPROUT_MATH_ASINH_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			asinh_impl(T x) {
				return sprout::math::log(x + sprout::math::sqrt(x * x + 1));
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			asinh(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::asinh(x)
#else
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::asinh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			asinh(IntType x) {
				return sprout::math::detail::asinh(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::asinh;
	}	// namespace math

	using sprout::math::asinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASINH_HPP
