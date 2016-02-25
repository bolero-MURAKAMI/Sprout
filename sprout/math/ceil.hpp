/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CEIL_HPP
#define SPROUT_MATH_CEIL_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_ceil(float x) {
				return __builtin_ceilf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_ceil(double x) {
				return __builtin_ceil(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_ceil(long double x) {
				return __builtin_ceill(x);
			}
#endif

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
		}	// namespace detail
		//
		// ceil
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		ceil(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_ceil(x)
#else
				: x == 0 ? x
				: sprout::numeric_limits<std::uintmax_t>::max() < x || sprout::numeric_limits<std::uintmax_t>::max() < -x
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
			return sprout::math::ceil(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::ceil;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CEIL_HPP
