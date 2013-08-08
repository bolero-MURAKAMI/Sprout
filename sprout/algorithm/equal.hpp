/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_EQUAL_HPP
#define SPROUT_ALGORITHM_EQUAL_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/functional/equal_to.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		equal_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return pivot == 0 ? pred(*first1, *first2)
				: sprout::detail::equal_impl_ra(
					first1, sprout::next(first1, pivot), first2, pred,
					pivot / 2
					)
					&& sprout::detail::equal_impl_ra(
						sprout::next(first1, pivot), last1, sprout::next(first2, pivot), pred,
						(sprout::distance(first1, last1) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		equal(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? true
				: sprout::detail::equal_impl_ra(
					first1, last1, first2, pred,
					sprout::distance(first1, last1) / 2
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		equal_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return !sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 ? current
				: n == 1 ? pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
					? type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), true)
					: type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), false)
				: sprout::detail::equal_impl_1(
					sprout::detail::equal_impl_1(
						current,
						last1, pred, n / 2
						),
					last1, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		equal_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return !sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 ? current
				: sprout::detail::equal_impl(
					sprout::detail::equal_impl_1(
						current,
						last1, pred, n
						),
					last1, pred, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		equal(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::tuples::get<2>(
				sprout::detail::equal_impl(type(first1, first2, true), last1, pred, 1)
				);
		}
	}	// namespace detail

	// 25.2.11 Equal
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::equal(first1, last1, first2, pred, category());
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		return sprout::equal(first1, last1, first2, sprout::equal_to<>());
	}

	namespace detail {
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR bool
		equal_impl_check(InputIterator1 last1, InputIterator2 last2, sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current) {
			return sprout::tuples::get<2>(current) && sprout::tuples::get<0>(current) == last1 && sprout::tuples::get<1>(current) == last2;
		}

		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		equal2_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return pivot == 0 ? pred(*first1, *first2)
				: sprout::detail::equal2_impl_ra(
					first1, sprout::next(first1, pivot), first2, sprout::next(first2, pivot), pred,
					pivot / 2
					)
					&& sprout::detail::equal2_impl_ra(
						sprout::next(first1, pivot), last1, sprout::next(first2, pivot), last2, pred,
						(sprout::distance(first1, last1) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			bool
		>::type
		equal(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::distance(first1, last1) == sprout::distance(first2, last2)
				&& sprout::detail::equal2_impl_ra(
					first1, last1, first2, last2, pred,
					sprout::distance(first1, last1) / 2
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		equal2_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return !sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: n == 1 ? pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
					? type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), true)
					: type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), false)
				: sprout::detail::equal2_impl_1(
					sprout::detail::equal2_impl_1(
						current,
						last1, last2, pred, n / 2
						),
					last1, last2, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		equal2_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return !sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: sprout::detail::equal2_impl(
					sprout::detail::equal2_impl_1(
						current,
						last1, last2, pred, n
						),
					last1, last2, pred, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		equal(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::detail::equal_impl_check(
				last1, last2,
				sprout::detail::equal2_impl(type(first1, first2, true), last1, last2, pred, 1)
				);
		}
	}	// namespace detail

	// 25.2.11 Equal
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::equal(first1, last1, first2, last2, pred, category());
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return sprout::equal(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_EQUAL_HPP
