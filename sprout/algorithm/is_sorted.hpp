#ifndef SPROUT_ALGORITHM_IS_SORTED_HPP
#define SPROUT_ALGORITHM_IS_SORTED_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/is_sorted_until.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.1.5 is_sorted
	template<typename ForwardIterator>
	SPROUT_CONSTEXPR bool is_sorted(ForwardIterator first, ForwardIterator last) {
		return sprout::is_sorted_until(first, last) == last;
	}

	template<typename ForwardIterator, typename Compare>
	SPROUT_CONSTEXPR bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
		return sprout::is_sorted_until(first, last, comp) == last;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_SORTED_HPP
