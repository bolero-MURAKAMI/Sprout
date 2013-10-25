/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FLOAT_SIGNIFICAND_HPP
#define SPROUT_MATH_FLOAT_SIGNIFICAND_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/float_exponent.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		//
		// float_significand
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		float_significand(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
				: x == 0 ? x
				: x / sprout::detail::pow_n(FloatType(sprout::numeric_limits<FloatType>::radix), sprout::float_exponent(x))
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		float_significand(IntType x) {
			return sprout::math::float_significand(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::float_significand;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_SIGNIFICAND_HPP
