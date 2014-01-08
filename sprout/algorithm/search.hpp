/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_SEARCH_HPP
#define SPROUT_ALGORITHM_SEARCH_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/detail/algorithm/search_one.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 last1_, RandomAccessIterator1 searched
			)
		{
			return searched < first1 || searched == last1_ ? searched
				: pivot == 0 ? sprout::detail::search_one(first1, last1_, first2, last2, pred)
				: sprout::detail::search_impl_ra(
					sprout::next(first1, pivot), last1, first2, last2, pred,
					(sprout::distance(first1, last1) - pivot) / 2, last1_,
					sprout::detail::search_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2, last1_,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			RandomAccessIterator1
		>::type
		search(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? last1
				: sprout::detail::search_impl_ra(
					first1, last1, first2, last2, pred,
					sprout::distance(first1, last1) / 2, last1, first1
					)
				;
		}

		template<typename ForwardIterator1>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		search_impl_fork(sprout::pair<ForwardIterator1, bool> const& current, ForwardIterator1 last1, ForwardIterator1 searched) {
			typedef sprout::pair<ForwardIterator1, bool> type;
			return searched == current.first || searched == last1 ? type(searched, true)
				: type(sprout::next(current.first), false)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		search_impl_1(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.second || current.first == last1 ? current
				: n == 1 ? sprout::detail::search_impl_fork(
					current, last1,
					sprout::detail::search_one(current.first, last1, first2, last2, pred)
					)
				: sprout::detail::search_impl_1(
					sprout::detail::search_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		search_impl(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.second || current.first == last1 ? current
				: sprout::detail::search_impl(
					sprout::detail::search_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return sprout::detail::search_impl(type(first1, false), last1, first2, last2, pred, 1).first;
		}
	}	// namespace detail

	// 25.2.13 Search
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<ForwardIterator1>::iterator_category* category;
		return sprout::detail::search(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::search(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_HPP
