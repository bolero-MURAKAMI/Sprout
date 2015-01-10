/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_NEXT_PERMUTATION_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_NEXT_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/next_permutation.hpp>

namespace sprout {
	namespace range {
		//
		// next_permutation
		//
		template<typename BidirectionalRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR bool
		next_permutation(BidirectionalRange&& rng, Compare comp) {
			return sprout::next_permutation(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)), comp);
		}

		template<typename BidirectionalRange>
		inline SPROUT_CXX14_CONSTEXPR bool
		next_permutation(BidirectionalRange&& rng) {
			return sprout::next_permutation(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_NEXT_PERMUTATION_HPP
