/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_TRUNC_HPP
#define SPROUT_MATH_TRUNC_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_trunc(float x) {
				return __builtin_truncf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_trunc(double x) {
				return __builtin_trunc(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_trunc(long double x) {
				return __builtin_truncl(x);
			}
#endif
		}	// namespace detail
		//
		// trunc
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		trunc(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				: sprout::math::detail::builtin_trunc(x)
#else
				: x == 0 ? x
				: sprout::numeric_limits<std::uintmax_t>::max() < x || sprout::numeric_limits<std::uintmax_t>::max() < -x
					? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("trunc: large float rounding."), x)
				: x < 0 ? -static_cast<FloatType>(static_cast<std::uintmax_t>(-x))
				: static_cast<FloatType>(static_cast<std::uintmax_t>(x))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		trunc(IntType x) {
			return sprout::math::trunc(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::trunc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TRUNC_HPP
