#ifndef SPROUT_MATH_CBRT_HPP
#define SPROUT_MATH_CBRT_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cbrt_impl(T x) {
				return x < 0 ? -sprout::pow(-x, sprout::math::third<T>())
					: sprout::pow(x, sprout::math::third<T>())
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			cbrt(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::cbrt(x)
#else
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::cbrt_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cbrt(IntType x) {
				return sprout::math::detail::cbrt(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::cbrt;
	}	// namespace math

	using sprout::math::cbrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CBRT_HPP
