#ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP
#define SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_heap.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.6.5 is_heap
		template<typename RandomAccessRange>
		inline SPROUT_CONSTEXPR bool
		is_heap(RandomAccessRange const& range) {
			return sprout::is_heap(sprout::begin(range), sprout::end(range));
		}

		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_heap(RandomAccessRange const& range, Compare comp) {
			return sprout::is_heap(sprout::begin(range), sprout::end(range), comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP
