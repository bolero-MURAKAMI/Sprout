#ifndef SPROUT_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_ALGORITHM_FIND_FIRST_OF_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.7 Find first
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1 find_first_of(
		ForwardIterator1 first1,
		ForwardIterator1 last1,
		ForwardIterator2 first2,
		ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		return first1 == last1 || sprout::find_if(first2, last2, NS_SSCRISK_CEL_OR_SPROUT::bind2nd(pred, *first1)) != last2 ? first1
			: sprout::find_first_of(sprout::next(first1), last1, first2, last2, pred)
			;
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1 find_first_of(
		ForwardIterator1 first1,
		ForwardIterator1 last1,
		ForwardIterator2 first2,
		ForwardIterator2 last2
		)
	{
		return first1 == last1 || sprout::find(first2, last2, *first1) != last2 ? first1
			: sprout::find_first_of(sprout::next(first1), last1, first2, last2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_FIRST_OF_HPP
