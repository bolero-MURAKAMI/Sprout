#ifndef SPROUT_ALGORITHM_LOWER_BOUND_HPP
#define SPROUT_ALGORITHM_LOWER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.1 lower_bound
	template<typename ForwardIterator, typename T>
	SPROUT_CONSTEXPR ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T const& value) {
		return first == last ? last
			: sprout::next(first) == last ? *first < value ? last : first
			: *sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2) < value
				? sprout::lower_bound(sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), last, value)
			: sprout::lower_bound(first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value)
			;
	}

	template<typename ForwardIterator, typename T, typename Compare>
	SPROUT_CONSTEXPR ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return first == last ? last
			: sprout::next(first) == last ? comp(*first, value) ? last : first
			: comp(*sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value)
				? sprout::lower_bound(sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), last, value, comp)
			: sprout::lower_bound(first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2), value, comp)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_LOWER_BOUND_HPP
