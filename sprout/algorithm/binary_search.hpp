#ifndef SPROUT_ALGORITHM_BINARY_SEARCH_HPP
#define SPROUT_ALGORITHM_BINARY_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.4 binary_search
	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR bool binary_search(ForwardIterator first, ForwardIterator last, T const& value) {
		return first == last ? false
			: sprout::next(first) == last ? !(*first < value) && !(value < *first) ? true : false
			: *sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2) < value
				? sprout::binary_search(sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), last, value)
			: value < *sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)) / 2
				? sprout::binary_search(first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value)
			: true
			;
	}

	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR bool binary_search(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return first == last ? false
			: sprout::next(first) == last ? !comp(*first, value) && !comp(value, *first) ? true : false
			: comp(*sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value)
				? sprout::binary_search(sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), last, value)
			: comp(value, *sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)) / 2)
				? sprout::binary_search(first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value)
			: true
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_BINARY_SEARCH_HPP
