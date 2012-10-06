#ifndef SPROUT_ALGORITHM_EQUAL_HPP
#define SPROUT_ALGORITHM_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.11 Equal
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		return first1 == last1 ? true
			: *first1 == *first2 && sprout::equal(sprout::next(first1), last1, sprout::next(first2))
			;
	}

	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		return first1 == last1 ? true
			: pred(*first1, *first2) != false && sprout::equal(sprout::next(first1), last1, sprout::next(first2), pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_EQUAL_HPP
