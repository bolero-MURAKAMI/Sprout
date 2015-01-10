/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_POP_HEAP_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_POP_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/pop_heap.hpp>

namespace sprout {
	namespace range {
		//
		// pop_heap
		//
		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		pop_heap(RandomAccessRange&& rng, Compare comp) {
			sprout::pop_heap(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)), comp);
		}

		template<typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR void
		pop_heap(RandomAccessRange&& rng) {
			sprout::pop_heap(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_POP_HEAP_HPP
