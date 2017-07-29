/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_NEXT_UNION_HPP
#define SPROUT_ALGORITHM_NEXT_UNION_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	//
	// next_union
	//
	//	recursion depth:
	//		O(1)
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_union(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		typedef sprout::pair<InputIterator1, InputIterator2> type;
		return first1 != last1
			? first2 != last2
				? comp(*first1, *first2)
					? type(sprout::next(first1), first2)
					: comp(*first2, *first1)
						? type(first1, sprout::next(first2))
						: type(sprout::next(first1), sprout::next(first2))
				: type(sprout::next(first1), first2)
			: first2 != last2
				? type(first1, sprout::next(first2))
			: type(last1, last2)
			;
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_union(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::next_union(first1, last1, first2, last2, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NEXT_UNION_HPP
