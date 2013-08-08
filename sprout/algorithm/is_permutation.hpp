/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
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

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return pivot == 0 ? sprout::count_if(first1, last1, sprout::bind2nd(pred, *first1))
					<= sprout::count_if(first2, last2, sprout::bind2nd(pred, *first1))
				: sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, last2,
					pred, pivot / 2
					)
					&& sprout::detail::is_permutation_impl_ra(
						sprout::next(first1, pivot), last1, first2, last2,
						pred, (sprout::distance(first1, last1) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		is_permutation(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? true
				: sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, sprout::next(first2, sprout::distance(first1, last1)),
					pred, sprout::distance(first1, last1) / 2
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		is_permutation_impl_1(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return !current.second || current.first == last1 ? current
				: n == 1 ? sprout::count_if(current.first, last1, sprout::bind2nd(pred, *current.first))
					<= sprout::count_if(first2, last2, sprout::bind2nd(pred, *current.first))
					? type(sprout::next(current.first), true)
					: type(current.first, false)
				: sprout::detail::is_permutation_impl_1(
					sprout::detail::is_permutation_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		is_permutation_impl(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return !current.second || current.first == last1 ? current
				: sprout::detail::is_permutation_impl(
					sprout::detail::is_permutation_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return sprout::detail::is_permutation_impl(type(first1, true), last1, first2, sprout::next(first2, sprout::distance(first1, last1)), pred, 1).second;
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
		return sprout::detail::is_permutation(first1, last1, first2, pred, category());
	}
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		return sprout::is_permutation(first1, last1, first2, sprout::equal_to<>());
	}

	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		is_permutation(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::distance(first1, last1) == sprout::distance(first2, last2)
				&& sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, last2,
					pred, sprout::distance(first1, last1) / 2
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator1, bool> type;
			return sprout::distance(first1, last1) == sprout::distance(first2, last2)
				&& sprout::detail::is_permutation_impl(type(first1, true), last1, first2, last2, pred, 1).second
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
