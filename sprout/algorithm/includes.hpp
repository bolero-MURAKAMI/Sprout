#ifndef SPROUT_ALGORITHM_INCLUDES_HPP
#define SPROUT_ALGORITHM_INCLUDES_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.5.1 includes
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return first2 == last2 ? true
			: first1 == last1 ? false
			: !(*first1 < *first2) && !(*first2 < *first1)
				? sprout::includes(sprout::next(first1), last1, sprout::next(first2), last2)
			: sprout::includes(sprout::next(first1), last1, first2, last2)
			;
	}

	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		return first2 == last2 ? true
			: first1 == last1 ? false
			: !comp(*first1, *first2) && !comp(*first2, *first1)
				? sprout::includes(sprout::next(first1), last1, sprout::next(first2), last2)
			: sprout::includes(sprout::next(first1), last1, first2, last2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INCLUDES_HPP
