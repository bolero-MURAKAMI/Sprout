/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_REV_HPP
#define SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_REV_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool>
		search_one_rev_impl_1(
			sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> const& current,
			BidirectionalIterator1 first1, BidirectionalIterator2 first2, BinaryPredicate pred,
			typename std::iterator_traits<BidirectionalIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: sprout::tuples::get<1>(current) == first2 ? type(sprout::tuples::get<0>(current), first2, true)
				: sprout::tuples::get<0>(current) == first1 ? type(first1, sprout::tuples::get<1>(current), true)
				: n == 1 ? pred(*sprout::prev(sprout::tuples::get<0>(current)), *sprout::prev(sprout::tuples::get<1>(current)))
						? type(sprout::prev(sprout::tuples::get<0>(current)), sprout::prev(sprout::tuples::get<1>(current)), false)
						: type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
				: sprout::detail::search_one_rev_impl_1(
					sprout::detail::search_one_rev_impl_1(
						current,
						first1, first2, pred, n / 2
						),
					first1, first2, pred, n - n / 2
					)
				;
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool>
		search_one_rev_impl(
			sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> const& current,
			BidirectionalIterator1 first1, BidirectionalIterator2 first2, BinaryPredicate pred,
			typename std::iterator_traits<BidirectionalIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: sprout::tuples::get<1>(current) == first2 ? type(sprout::tuples::get<0>(current), first2, true)
				: sprout::tuples::get<0>(current) == first1 ? type(first1, sprout::tuples::get<1>(current), true)
				: sprout::detail::search_one_rev_impl(
					sprout::detail::search_one_rev_impl_1(
						current,
						first1, first2, pred, n
						),
					first1, first2, pred, n * 2
					)
				;
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, bool>
		search_one_rev_check(
			sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> const& result,
			BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2
			)
		{
			typedef sprout::pair<BidirectionalIterator1, bool> type;
			return sprout::tuples::get<1>(result) == first2 ? type(sprout::tuples::get<0>(result), false)
				: type(last1, sprout::tuples::get<0>(result) == first1)
				;
		}

		//
		// search_one_rev
		//
		//	recursion depth:
		//		O(log(N1+N2))
		//
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, bool>
		search_one_rev(
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2, BinaryPredicate pred
			)
		{
			typedef sprout::tuples::tuple<BidirectionalIterator1, BidirectionalIterator2, bool> type;
			return sprout::detail::search_one_rev_check(
				sprout::detail::search_one_rev_impl(type(last1, last2, false), first1, first2, pred, 1),
				first1, last1, first2);
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, bool>
		search_one_rev(
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2
			)
		{
			return sprout::detail::search_one_rev(first1, last1, first2, last2, sprout::equal_to<>());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_REV_HPP
