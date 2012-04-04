#ifndef SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.8 Lexicographical comparison
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR bool lexicographical_compare(
		InputIterator1 first1,
		InputIterator1 last1,
		InputIterator2 first2,
		InputIterator2 last2,
		Compare comp
		)
	{
		return first2 == last2 ? false
			: first1 == last1 || comp(*first1, *first2) ? true
			: comp(*first2, *first1) ? false
			: sprout::lexicographical_compare(sprout::next(first1), last1, sprout::next(first2), last2, comp)
			;
	}

	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool lexicographical_compare(
		InputIterator1 first1,
		InputIterator1 last1,
		InputIterator2 first2,
		InputIterator2 last2
		)
	{
		return sprout::lexicographical_compare(first1, last1, first2, last2, NS_SSCRISK_CEL_OR_SPROUT::less<decltype(*first1 + *first2)>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
