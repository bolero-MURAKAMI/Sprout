#ifndef SPROUT_ALGORITHM_LOWER_BOUND_HPP
#define SPROUT_ALGORITHM_LOWER_BOUND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.1 lower_bound
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	lower_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return first == last ? last
			: sprout::next(first) == last ? comp(*first, value) ? last : first
			: comp(*sprout::next(first, sprout::distance(first, last) / 2), value)
				? sprout::lower_bound(sprout::next(first, sprout::distance(first, last) / 2), last, value, comp)
			: sprout::lower_bound(first, sprout::next(first, sprout::distance(first, last) / 2), value, comp)
			;
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	lower_bound(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::lower_bound(
			first, last, value,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_LOWER_BOUND_HPP
