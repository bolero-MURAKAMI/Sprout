/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP
#define SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_decreasing.hpp>

namespace sprout {
	namespace range {
		//
		// is_decreasing
		//
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR bool
		is_decreasing(ForwardRange const& range) {
			return sprout::is_decreasing(sprout::begin(range), sprout::end(range));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP
