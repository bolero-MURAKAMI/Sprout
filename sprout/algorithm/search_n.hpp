/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
#define SPROUT_ALGORITHM_SEARCH_N_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/tuple.hpp>
#include <sprout/algorithm/find.hpp>
#include <sprout/algorithm/find_if.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		search_n_impl_ra(
			RandomAccessIterator current, RandomAccessIterator last,
			Size count, T const& value, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type len,
			RandomAccessIterator searched
			)
		{
			return sprout::distance(searched, current) >= count || searched == last ? searched
				: len == 1 ? pred(*current, value) ? searched
					: sprout::distance(current, last) > count ? sprout::next(current) : last
				: sprout::detail::search_n_impl_ra(
					current + len / 2, last, count, value, pred, len - len / 2,
					sprout::detail::search_n_impl_ra(
						current, last, count, value, pred, len / 2, searched
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		search_n(
			RandomAccessIterator first, RandomAccessIterator last, Size count, T const& value, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::distance(first, last) < count
				? last
				: sprout::detail::search_n_impl_ra(
					first, last, count, value, pred, sprout::distance(first, last), first
					)
				;
		}
		template<typename ForwardIterator, typename Size>
		inline SPROUT_CONSTEXPR ForwardIterator
		search_n_impl_check(
			sprout::tuple<ForwardIterator, ForwardIterator, Size> current,
			ForwardIterator last, Size count
			)
		{
			return sprout::tuples::get<2>(current) == count ? sprout::tuples::get<1>(current) : last;
		}
		template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuple<ForwardIterator, ForwardIterator, Size>
		search_n_impl_1(
			sprout::tuple<ForwardIterator, ForwardIterator, Size> current,
			ForwardIterator last, Size count, T const& value, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::tuple<ForwardIterator, ForwardIterator, Size> type;
			return sprout::tuples::get<2>(current) == count || sprout::tuples::get<0>(current) == last ? current
				: n == 1
				? pred(*sprout::tuples::get<0>(current), value)
					? type(sprout::next(sprout::tuples::get<0>(current)), sprout::tuples::get<1>(current), sprout::tuples::get<2>(current) + 1)
					: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<0>(current)), 0)
				: sprout::detail::search_n_impl_1(
					sprout::detail::search_n_impl_1(
						current,
						last, count, value, pred, n / 2
						),
					last, count, value, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuple<ForwardIterator, ForwardIterator, Size>
		search_n_impl(
			sprout::tuple<ForwardIterator, ForwardIterator, Size> current,
			ForwardIterator last, Size count, T const& value, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			return sprout::tuples::get<2>(current) == count || sprout::tuples::get<0>(current) == last ? current
				: sprout::detail::search_n_impl(
					sprout::detail::search_n_impl_1(
						current,
						last, count, value, pred, n
						),
					last, count, value, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		search_n(
			ForwardIterator first, ForwardIterator last, Size count, T const& value, BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::tuple<ForwardIterator, ForwardIterator, Size> type;
			return sprout::detail::search_n_impl_check(
				sprout::detail::search_n_impl(type(first, first, 0), last, count, value, pred, 1),
				last, count
				)
				;
		}
	}
	// 25.2.13 Search
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value, BinaryPredicate pred) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return count == 0 ? last : count == 1 ? sprout::find_if(first, last, sprout::bind2nd(pred, value))
			: sprout::detail::search_n(first, last, count, value, pred, category());
	}

	template<typename ForwardIterator, typename Size, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return count == 0 ? last : count == 1 ? sprout::find(first, last, value)
			: sprout::detail::search_n(first, last, count, value, sprout::equal_to<>(), category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
