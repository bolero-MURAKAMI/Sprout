#ifndef SPROUT_ALGORITHM_IS_HEAP_HPP
#define SPROUT_ALGORITHM_IS_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/is_heap_until.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.6.5 is_heap
	template<typename RandomAccessIterator>
	SPROUT_CONSTEXPR bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return sprout::is_heap_until(first, last) == last;
	}

	template<typename RandomAccessIterator, typename Compare>
	SPROUT_CONSTEXPR bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		return sprout::is_heap_until(first, last, comp) == last;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_HEAP_HPP
