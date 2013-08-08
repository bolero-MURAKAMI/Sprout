/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SINH_HPP
#define SPROUT_MATH_SINH_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinh_impl_1(T t) {
				return T(0.5) * t - T(0.5) / t;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			sinh_impl(T x) {
				return sprout::math::detail::sinh_impl_1(sprout::math::exp(x));
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			sinh(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
					: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::sinh(x)
#else
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::sinh_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			sinh(IntType x) {
				return sprout::math::detail::sinh(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::sinh;
	}	// namespace math

	using sprout::math::sinh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SINH_HPP
