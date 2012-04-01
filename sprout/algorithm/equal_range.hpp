#ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
#define SPROUT_ALGORITHM_EQUAL_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/lower_bound.hpp>
#include <sprout/algorithm/upper_bound.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.3.3 equal_range
	template<typename ForwardIterator, typename T>
	SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator> equal_range(
		ForwardIterator first,
		ForwardIterator last,
		T const& value
		)
	{
		return {sprout::lower_bound(first, last, value), sprout::upper_bound(first, last, value)};
	}

	template<typename ForwardIterator, typename T, typename Compare>
	SPROUT_CONSTEXPR pair<ForwardIterator, ForwardIterator> equal_range(
		ForwardIterator first,
		ForwardIterator last,
		T const& value,
		Compare comp
		)
	{
		return {sprout::lower_bound(first, last, value, comp), sprout::upper_bound(first, last, value, comp)};
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
