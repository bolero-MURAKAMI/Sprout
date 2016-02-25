/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ASINH_HPP
#define SPROUT_MATH_ASINH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_asinh(float x) {
				return __builtin_asinhf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_asinh(double x) {
				return __builtin_asinh(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_asinh(long double x) {
				return __builtin_asinhl(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			asinh_impl(T x) {
				return sprout::math::log(x + sprout::math::sqrt(x * x + 1));
			}
		}	// namespace detail
		//
		// asinh
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		asinh(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_asinh(x)
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
			return sprout::math::asinh(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::asinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ASINH_HPP
