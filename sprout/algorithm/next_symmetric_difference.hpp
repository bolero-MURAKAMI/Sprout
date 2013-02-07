#ifndef SPROUT_ALGORITHM_NEXT_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_ALGORITHM_NEXT_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/find_symmetric_difference.hpp>

namespace sprout {
	//
	// next_symmetric_difference
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_symmetric_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		typedef sprout::pair<InputIterator1, InputIterator2> type;
		return first1 != last1
			? first2 != last2
				? comp(*first1, *first2)
					? sprout::find_symmetric_difference(sprout::next(first1), last1, first2, last2, comp)
					: sprout::find_symmetric_difference(first1, last1, sprout::next(first2), last2, comp)
				: type(sprout::next(first1), first2)
			: first2 != last2
				? type(first1, sprout::next(first2))
			: type(last1, last2)
			;
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	next_symmetric_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::next_symmetric_difference(first1, last1, first2, last2, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NEXT_SYMMETRIC_DIFFERENCE_HPP
