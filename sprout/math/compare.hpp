/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_COMPARE_HPP
#define SPROUT_MATH_COMPARE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/math/less.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		//
		// compare
		//
		template<
			typename T, typename U,
			typename sprout::enabler_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		compare(T x, U y) {
			return sprout::math::equal_to(x, y) ? 0
				: sprout::math::less(x, y) ? -1
				: 1
				;
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COMPARE_HPP
