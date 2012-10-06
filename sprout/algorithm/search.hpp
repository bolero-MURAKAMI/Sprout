#ifndef SPROUT_ALGORITHM_SEARCH_HPP
#define SPROUT_ALGORITHM_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.13 Search
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return first1 == last1 || first2 == last2 ? first1
			: NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) < NS_SSCRISK_CEL_OR_SPROUT::distance(first2, last2) ? last1
			: *first1 == *first2
				&& sprout::search(sprout::next(first1), last1, sprout::next(first2), last2) == sprout::next(first1)
				? first1
			: sprout::search(sprout::next(first1), last1, first2, last2)
			;
	}

	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		return first1 == last1 || first2 == last2 ? first1
			: NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) < NS_SSCRISK_CEL_OR_SPROUT::distance(first2, last2) ? last1
			: *first1 == *first2
				&& sprout::search(sprout::next(first1), last1, sprout::next(first2), last2, pred) == sprout::next(first1)
				? first1
			: sprout::search(sprout::next(first1), last1, first2, last2, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_HPP
