/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIND_END_HPP
#define SPROUT_ALGORITHM_FIND_END_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/detail/algorithm/search_one.hpp>
#include <sprout/detail/algorithm/search_one_rev.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_check_ra(RandomAccessIterator1 first1, RandomAccessIterator1 last1_, RandomAccessIterator1 searched) {
			return searched == first1 ? searched
				: last1_
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 last1_,
			RandomAccessIterator1 searched
			)
		{
			return searched != last1_ ? searched
				: pivot == 0
				? sprout::detail::find_end_impl_check_ra(
					first1, last1_,
					sprout::detail::search_one(first1, last1_, first2, last2, pred)
					)
				: sprout::detail::find_end_impl_ra(
					first1, sprout::next(first1, pivot), first2, last2, pred,
					pivot / 2, last1_,
					sprout::detail::find_end_impl_ra(
						sprout::next(first1, pivot), last1, first2, last2, pred,
						(sprout::distance(first1, last1) - pivot) / 2, last1_,
						last1_
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_ra1(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type len1,
			typename std::iterator_traits<RandomAccessIterator2>::difference_type len2
			)
		{
			return len1 < len2 ? last1
				: sprout::detail::find_end_impl_ra(
					first1, last1 - len2 + 1, first2, last2, pred,
					(len1 - len2 + 1) / 2, last1, last1
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			RandomAccessIterator1
		>::type
		find_end(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::detail::find_end_impl_ra1(
					first1, last1, first2, last2, pred,
					sprout::distance(first1, last1), sprout::distance(first2, last2)
					)
				;
		}

		template<typename BidirectionalIterator1>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, BidirectionalIterator1>
		find_end_impl_check_bi(
			sprout::pair<BidirectionalIterator1, BidirectionalIterator1> const& current,
			BidirectionalIterator1 first1, sprout::pair<BidirectionalIterator1, bool> searched
			)
		{
			typedef sprout::pair<BidirectionalIterator1, BidirectionalIterator1> type;
			return searched.second ? type(first1, current.second)
				: searched.first == current.first ? type(sprout::prev(current.first), current.second)
				: type(current.first, searched.first)
				;
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, BidirectionalIterator1>
		find_end_impl_bi1(
			sprout::pair<BidirectionalIterator1, BidirectionalIterator1> const& current,
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<BidirectionalIterator1>::difference_type n
			)
		{
			return current.second != last1 || current.first == first1 ? current
				: n == 1 ? sprout::detail::find_end_impl_check_bi(
					current, first1,
					sprout::detail::search_one_rev(first1, current.first, first2, last2, pred)
					)
				: sprout::detail::find_end_impl_bi1(
					sprout::detail::find_end_impl_bi1(
						current,
						first1, last1, first2, last2, pred, n / 2
						),
					first1, last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<BidirectionalIterator1, BidirectionalIterator1>
		find_end_impl_bi(
			sprout::pair<BidirectionalIterator1, BidirectionalIterator1> const& current,
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<BidirectionalIterator1>::difference_type n
			)
		{
			return current.second != last1 || current.first == first1 ? current
				: sprout::detail::find_end_impl_bi(
					sprout::detail::find_end_impl_bi1(
						current,
						first1, last1, first2, last2, pred, n
						),
					first1, last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR BidirectionalIterator1
		find_end(
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			BinaryPredicate pred,
			std::bidirectional_iterator_tag*
			)
		{
			typedef sprout::pair<BidirectionalIterator1, BidirectionalIterator1> type;
			return sprout::detail::find_end_impl_bi(type(last1, last1), first1, last1, first2, last2, pred, 1).second;
		}

		template<typename ForwardIterator1>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_check(sprout::pair<ForwardIterator1, ForwardIterator1> const& current, ForwardIterator1 last1, ForwardIterator1 searched) {
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return searched == current.first ? type(sprout::next(current.first), searched)
				: searched == last1 ? type(last1, current.second)
				: type(sprout::next(current.first), current.second)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_1(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.first == last1 ? current
				: n == 1 ? sprout::detail::find_end_impl_check(
					current, last1,
					sprout::detail::search_one(current.first, last1, first2, last2, pred)
					)
				: sprout::detail::find_end_impl_1(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.first == last1 ? current
				: sprout::detail::find_end_impl(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return sprout::detail::find_end_impl(type(first1, last1), last1, first2, last2, pred, 1).second;
		}
	}	// namespace detail

	// 25.2.6 Find end
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
		return first1 == last1 || first2 == last2 ? last1 : sprout::detail::find_end(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::find_end(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_END_HPP
