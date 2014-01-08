/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_EXP10_HPP
#define SPROUT_MATH_EXP10_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp10_impl(T x) {
				return sprout::math::exp(x * sprout::math::ln_ten<T>());
			}
		}	// namespace detail
		//
		// exp10
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		exp10(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == -sprout::numeric_limits<FloatType>::infinity() ? FloatType(0)
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == 0 ? FloatType(1)
				: static_cast<FloatType>(sprout::math::detail::exp10_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		exp10(IntType x) {
			return sprout::math::exp10(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::exp10;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP10_HPP
