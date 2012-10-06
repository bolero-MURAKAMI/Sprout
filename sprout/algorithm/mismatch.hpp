#ifndef SPROUT_ALGORITHM_MISMATCH_HPP
#define SPROUT_ALGORITHM_MISMATCH_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.10 Mismatch
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		return first1 == last1 || !(*first1 == *first2)
			? sprout::pair<InputIterator1, InputIterator2>{first1, first2}
			: sprout::mismatch(sprout::next(first1), last1, sprout::next(first2))
			;
	}

	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		return first1 == last1 || pred(*first1, *first2) == false
			? sprout::pair<InputIterator1, InputIterator2>{first1, first2}
			: sprout::mismatch(sprout::next(first1), last1, sprout::next(first2))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MISMATCH_HPP
