#ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
#define SPROUT_ALGORITHM_UPPER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.2 upper_bound
	template<typename ForwardIterator, typename T>
	SPROUT_CONSTEXPR ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T const& value) {
		return first == last ? last
			: sprout::next(first) == last ? !(value < *first) ? last : first
			: !(value < *(first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2))
				? upper_bound(first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, last, value)
			: sprout::upper_bound(first, first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, value)
			;
	}

	template<typename ForwardIterator, typename T, typename Compare>
	SPROUT_CONSTEXPR ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return first == last ? last
			: sprout::next(first) == last ? !comp(value, *first) ? last : first
			: !comp(value, *(first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2))
				? sprout::upper_bound(first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, last, value, comp)
			: sprout::upper_bound(first, first + NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2, value, comp)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
