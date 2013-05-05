#ifndef SPROUT_MATH_ERFC_HPP
#define SPROUT_MATH_ERFC_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/erf.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erfc_impl(T x) {
				return T(1) - sprout::math::erf(x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			erfc(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == std::numeric_limits<FloatType>::infinity() ? FloatType(0)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(2)
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::erfc(x)
#else
					: static_cast<FloatType>(sprout::math::detail::erfc_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			erfc(IntType x) {
				return sprout::math::detail::erfc(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::erfc;
	}	// namespace math

	using sprout::math::erfc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ERFC_HPP
