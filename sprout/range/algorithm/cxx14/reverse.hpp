/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/reverse.hpp>

namespace sprout {
	namespace range {
		//
		// reverse
		//
		template<typename BidirectionalRange>
		inline SPROUT_CXX14_CONSTEXPR void
		reverse(BidirectionalRange&& rng) {
			sprout::reverse(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_HPP
