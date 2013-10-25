/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FLOAT2_EXPONENT_HPP
#define SPROUT_MATH_FLOAT2_EXPONENT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/ilogb2.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		//
		// float2_exponent
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float2_exponent(FloatType x) {
			return sprout::math::isnan(x) ? 0
				: x == 0 ? 0
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity() ? 0
				: sprout::math::ilogb2(x) + 1
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float2_exponent(IntType x) {
			return sprout::math::float2_exponent(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::float2_exponent;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT2_EXPONENT_HPP
