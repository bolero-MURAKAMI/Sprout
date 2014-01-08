/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP
#define SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/algorithm/mismatch.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_one_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2, BinaryPredicate pred
			)
		{
			return sprout::mismatch(first1, last1, first2, pred).first == last1 ? first1
				: last1
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_one(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::distance(first1, last1) < sprout::distance(first2, last2) ? last1
				: first1 == last1 ? first1
				: sprout::detail::search_one_impl_ra(
					first1, sprout::next(first1, sprout::distance(first2, last2)), first2, last2, pred
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool>
		search_one_impl_1(
			sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 last2, BinaryPredicate pred,
			ForwardIterator1 first1_, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: sprout::tuples::get<1>(current) == last2 ? type(first1_, last2, true)
				: sprout::tuples::get<0>(current) == last1 ? type(last1, last2, true)
				: n == 1 ? !pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
						? type(sprout::next(sprout::tuples::get<0>(current)), last2, true)
						: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), false)
				: sprout::detail::search_one_impl_1(
					sprout::detail::search_one_impl_1(
						current,
						last1, last2, pred, first1_, n / 2
						),
					last1, last2, pred, first1_, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool>
		search_one_impl(
			sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> const& current,
			ForwardIterator1 last1, ForwardIterator2 last2, BinaryPredicate pred,
			ForwardIterator1 first1_, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: sprout::tuples::get<1>(current) == last2 ? type(first1_, last2, true)
				: sprout::tuples::get<0>(current) == last1 ? type(last1, last2, true)
				: sprout::detail::search_one_impl(
					sprout::detail::search_one_impl_1(
						current,
						last1, last2, pred, first1_, n
						),
					last1, last2, pred, first1_, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<0>(sprout::detail::search_one_impl(type(first1, first2, false), last1, last2, pred, first1, 1));
		}

		//
		// search_one
		//
		//	recursion depth:
		//		O(log(N1+N2))
		//
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
			typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
			return sprout::detail::search_one(first1, last1, first2, last2, pred, category());
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
			return sprout::detail::search_one(first1, last1, first2, last2, sprout::equal_to<>());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP
