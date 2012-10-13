#ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
#define SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.1.5 is_sorted
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last) {
		return first == last || sprout::next(first) == last ? last
			: *(sprout::next(first)) < *first ? sprout::next(first)
			: sprout::is_sorted_until(sprout::next(first), last)
			;
	}

	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp) {
		return first == last || sprout::next(first) == last ? last
			: comp(*(sprout::next(first)), *first) ? sprout::next(first)
			: sprout::is_sorted_until(sprout::next(first), last)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
