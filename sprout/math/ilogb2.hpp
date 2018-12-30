/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ILOGB2_HPP
#define SPROUT_MATH_ILOGB2_HPP

#include <climits>
#include <cfloat>
#include <cmath>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_FLT_RADIX_IS_2
#	include <sprout/math/ilogb.hpp>
#else
#	include <sprout/math/logb2.hpp>
#	include <sprout/math/isnan.hpp>
#	include <sprout/math/isinf.hpp>
#	include <sprout/math/iszero.hpp>
#endif

namespace sprout {
	namespace math {
#if SPROUT_FLT_RADIX_IS_2
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb2(FloatType x) {
			return sprout::math::ilogb(x);
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb2(IntType x) {
			return sprout::math::ilogb(x);
		}
#else
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb2(FloatType x) {
			return sprout::math::iszero(x) ? FP_ILOGB0
				: sprout::math::isinf(x) ? INT_MAX
				: sprout::math::isnan(x) ? FP_ILOGBNAN
				: static_cast<int>(sprout::math::logb2(x))
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		ilogb2(IntType x) {
			return sprout::math::ilogb2(static_cast<double>(x));
		}
#endif
	}	// namespace math

	using sprout::math::ilogb2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ILOGB2_HPP
