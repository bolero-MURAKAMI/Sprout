#ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
#define SPROUT_ALGORITHM_EQUAL_RANGE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/lower_bound.hpp>
#include <sprout/algorithm/upper_bound.hpp>
#include <sprout/utility/pair/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.3 equal_range
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	equal_range(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return sprout::pair<ForwardIterator, ForwardIterator>{
			sprout::lower_bound(first, last, value, comp),
			sprout::upper_bound(first, last, value, comp)
			};
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	equal_range(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::equal_range(
			first, last, value,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
