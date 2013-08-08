/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_MISMATCH_HPP
#define SPROUT_ALGORITHM_MISMATCH_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/utility/pair/pair.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		mismatch_impl_check(RandomAccessIterator1 first1, RandomAccessIterator2 first2, RandomAccessIterator1 found) {
			return sprout::pair<RandomAccessIterator1, RandomAccessIterator2>{
				found, sprout::next(first2, sprout::distance(first1, found))
				};
		}

		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		mismatch_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 found
			)
		{
			return found != first1 ? found
				: pivot == 0 ? (!pred(*first1, *first2) ? first1 : last1)
				: sprout::detail::mismatch_impl_ra(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), pred,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::mismatch_impl_ra(
						first1, sprout::next(first1, pivot), first2, pred,
						pivot / 2,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		>::type
		mismatch(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? sprout::pair<RandomAccessIterator1, RandomAccessIterator2>{first1, first2}
				: sprout::detail::mismatch_impl_check(
					first1, first2,
					sprout::detail::mismatch_impl_ra(
						first1, last1, first2, pred,
						sprout::distance(first1, last1) / 2, first1
						)
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch_impl_check(sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current) {
			return sprout::pair<InputIterator1, InputIterator2>(
				sprout::tuples::get<0>(current),
				sprout::tuples::get<1>(current)
				);
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		mismatch_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 ? current
				: n == 1 ? !pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
					? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
					: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), false)
				: sprout::detail::mismatch_impl_1(
					sprout::detail::mismatch_impl_1(
						current,
						last1, pred, n / 2
						),
					last1, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		mismatch_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 ? current
				: sprout::detail::mismatch_impl(
					sprout::detail::mismatch_impl_1(
						current,
						last1, pred, n
						),
					last1, pred, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::detail::mismatch_impl_check(
				sprout::detail::mismatch_impl(type(first1, first2, false), last1, pred, 1)
				);
		}
	}	// namespace detail

	// 25.2.10 Mismatch
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::mismatch(first1, last1, first2, pred, category());
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		return sprout::mismatch(first1, last1, first2, sprout::equal_to<>());
	}

	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		mismatch2_impl_ra_1(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 found
			)
		{
			return found != first1 ? found
				: pivot == 0 ? (!pred(*first1, *first2) ? first1 : last1)
				: sprout::detail::mismatch2_impl_ra_1(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), last2, pred,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::mismatch2_impl_ra_1(
						first1, sprout::next(first1, pivot), first2, sprout::next(first2, pivot), pred,
						pivot / 2,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		mismatch2_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1, RandomAccessIterator2 first2, RandomAccessIterator2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size
			)
		{
			return sprout::detail::mismatch2_impl_ra_1(
				first1, sprout::next(first1, size), first2, sprout::next(first2, size), pred,
				size / 2, first1
				);
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value && sprout::is_constant_distance_iterator<RandomAccessIterator2>::value,
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		>::type
		mismatch(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 || first2 == last2 ? sprout::pair<RandomAccessIterator1, RandomAccessIterator2>{first1, first2}
				: sprout::detail::mismatch_impl_check(
					first1, first2,
					sprout::detail::mismatch2_impl_ra(
						first1, last1, first2, last2, pred,
						NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first1, last1), sprout::distance(first2, last2))
						)
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch2_impl_check(sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current) {
			return sprout::pair<InputIterator1, InputIterator2>(
				sprout::tuples::get<0>(current),
				sprout::tuples::get<1>(current)
				);
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		mismatch2_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: n == 1 ? !pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
					? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
					: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), false)
				: sprout::detail::mismatch2_impl_1(
					sprout::detail::mismatch2_impl_1(
						current,
						last1, last2, pred, n / 2
						),
					last1, last2, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		mismatch2_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, BinaryPredicate pred, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: sprout::detail::mismatch2_impl(
					sprout::detail::mismatch2_impl_1(
						current,
						last1, last2, pred, n
						),
					last1, last2, pred, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::detail::mismatch2_impl_check(
				sprout::detail::mismatch2_impl(type(first1, first2, false), last1, last2, pred, 1)
				);
		}
	}	// namespace detail

	// 25.2.10 Mismatch
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::mismatch(first1, last1, first2, last2, pred, category());
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return sprout::mismatch(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MISMATCH_HPP
