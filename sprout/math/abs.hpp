/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ABS_HPP
#define SPROUT_MATH_ABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/fabs.hpp>

namespace sprout {
	namespace math {
		//
		// abs
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		abs(FloatType x) {
				return sprout::math::fabs(x);
		}
	}	// namespace math

	using sprout::math::abs;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ABS_HPP
