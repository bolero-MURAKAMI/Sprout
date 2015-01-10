/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SCALBLN_HPP
#define SPROUT_MATH_SCALBLN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_scalbln(float x, long exp) {
				return __builtin_scalblnf(x, exp);
			}
			inline SPROUT_CONSTEXPR double
			builtin_scalbln(double x, long exp) {
				return __builtin_scalbln(x, exp);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_scalbln(long double x, long exp) {
				return __builtin_scalblnl(x, exp);
			}
#endif

			template<typename FloatType, typename T>
			inline SPROUT_CONSTEXPR T
			scalbln_impl(T x, long exp) {
				return x * sprout::detail::pow_n(T(sprout::numeric_limits<FloatType>::radix), exp);
			}
		}	// namespace detail
		//
		// scalbln
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		scalbln(FloatType x, long exp) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_scalbln(x, exp)
#else
				sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
				: exp == 0 ? x
				: x == 0 ? x
				: static_cast<FloatType>(sprout::math::detail::scalbln_impl<FloatType>(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x), exp))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		scalbln(IntType x, long exp) {
			return sprout::math::scalbln(static_cast<double>(x), exp);
		}
	}	// namespace math

	using sprout::math::scalbln;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SCALBLN_HPP
