/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
#define SPROUT_ALGORITHM_IS_PERMUTATION_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/algorithm/count_if.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/algorithm/mismatch.hpp>

namespace sprout {
	namespace detail {
		template<typename Difference, typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_check(Difference count, ForwardIterator const& first, ForwardIterator const& last, BinaryPredicate pred)
		{
			return count != 0 && sprout::count_if(sprout::next(first), last, sprout::bind2nd(pred, *first)) + 1 == count;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_ra(
			RandomAccessIterator1 const& first1, RandomAccessIterator1 const& last1,
			RandomAccessIterator2 const& first2, RandomAccessIterator2 const& last2,
			BinaryPredicate pred, RandomAccessIterator1 const& current,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size
			)
		{
			return size == 1 ? sprout::find_if(first1, current, sprout::bind2nd(pred, *current)) != current
					|| sprout::detail::is_permutation_impl_check(
						sprout::count_if(first2, last2, sprout::bind2nd(pred, *current)),
						current, last1, pred
						)
				: sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, last2,
					pred, current, size / 2
					)
					&& sprout::detail::is_permutation_impl_ra(
						first1, last1, first2, last2,
						pred, sprout::next(current, size / 2), size - size / 2
						)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		is_permutation(
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2> first, RandomAccessIterator1 const& last1, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first.first == last1
				|| sprout::detail::is_permutation_impl_ra(
					first.first, last1, first.second, sprout::next(first.second, sprout::distance(first.first, last1)),
					pred, first.first, sprout::distance(first.first, last1)
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		is_permutation_impl_1(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator1 const& first1, ForwardIterator1 const& last1, ForwardIterator2 const& first2, ForwardIterator2 const& last2,
			BinaryPredicate pred, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return !current.second || current.first == last1 ? current
				: n == 1 ? sprout::find_if(first1, current.first, sprout::bind2nd(pred, *current.first)) != current.first
					|| sprout::detail::is_permutation_impl_check(
						sprout::count_if(first2, last2, sprout::bind2nd(pred, *current.first)),
						current.first, last1, pred
						)
					? type(sprout::next(current.first), true)
					: type(current.first, false)
				: sprout::detail::is_permutation_impl_1(
					sprout::detail::is_permutation_impl_1(
						current,
						first1, last1, first2, last2, pred, n / 2
						),
					first1, last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 const& first1, ForwardIterator1 const& last1, ForwardIterator2 const& first2,
			BinaryPredicate pred, typename std::iterator_traits<ForwardIterator1>::difference_type size
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return sprout::detail::is_permutation_impl_1(
					type(first1, true),
					first1, last1, first2, sprout::next(first2, size),
					pred, size
					).second
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			sprout::pair<ForwardIterator1, ForwardIterator2> first, ForwardIterator1 const& last1, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			return first.first == last1
				|| sprout::detail::is_permutation_impl(
					first.first, last1, first.second, pred, sprout::distance(first.first, last1)
					)
				;
		}
	}	// namespace detail

	// 25.2.12 Is permutation
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
		return sprout::detail::is_permutation(sprout::mismatch(first1, last1, first2, pred), last1, pred, category());
	}
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		return sprout::is_permutation(first1, last1, first2, sprout::equal_to<>());
	}

	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_ra_1(
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2> first,
			RandomAccessIterator1 const& last1, RandomAccessIterator2 const& last2, BinaryPredicate pred
			)
		{
			return first.first == last1
				|| sprout::detail::is_permutation_impl_ra(
					first.first, last1, first.second, last2,
					pred, first.first, sprout::distance(first.first, last1)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		is_permutation(
			RandomAccessIterator1 const& first1, RandomAccessIterator1 const& last1, RandomAccessIterator2 const& first2, RandomAccessIterator2 const& last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::distance(first1, last1) == sprout::distance(first2, last2)
				&& sprout::detail::is_permutation_impl_ra_1(
					sprout::mismatch(first1, last1, first2, last2, pred),
					last1, last2, pred)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate, typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_3(
			ForwardIterator1 const& first1, ForwardIterator1 const& last1,
			ForwardIterator2 const& first2, ForwardIterator2 const& last2, BinaryPredicate pred,
			Difference1 size1, Difference2 size2
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return size1 == size2
				&& sprout::detail::is_permutation_impl_1(
					type(first1, true), first1, last1, first2, last2,
					pred, size1
					).second
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_2(
			sprout::pair<ForwardIterator1, ForwardIterator2> first,
			ForwardIterator1 const& last1, ForwardIterator2 const& last2, BinaryPredicate pred
			)
		{
			return sprout::detail::is_permutation_impl_3(
				first.first, last1, first.second, last2, pred,
				sprout::distance(first.first, last1), sprout::distance(first.second, last2)
				)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			ForwardIterator1 const& first1, ForwardIterator1 const& last1, ForwardIterator2 const& first2, ForwardIterator2 const& last2, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			return sprout::detail::is_permutation_impl_2(
				sprout::mismatch(first1, last1, first2, last2, pred),
				last1, last2, pred);
		}
	}	// namespace detail

	// 25.2.12 Is permutation
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
		return sprout::detail::is_permutation(first1, last1, first2, last2, pred, category());
	}
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
		return sprout::is_permutation(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
