/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_NEXT_INTERSECTION_HPP
#define SPROUT_ALGORITHM_NEXT_INTERSECTION_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/find_intersection.hpp>

namespace sprout {
	//
	// next_intersection
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_intersection(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		typedef sprout::pair<InputIterator1, InputIterator2> type;
		return first1 == last1 || first2 == last2 ? type(last1, last2)
			: sprout::find_intersection(sprout::next(first1), last1, sprout::next(first2), last2, comp)
			;
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_intersection(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::next_intersection(first1, last1, first2, last2, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NEXT_INTERSECTION_HPP
