/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIND_IF_NOT_HPP
#define SPROUT_ALGORITHM_FIND_IF_NOT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find_if_not_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (!pred(*first) ? first : last)
				: sprout::detail::find_if_not_impl_ra(
					sprout::next(first, pivot), last, pred,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::find_if_not_impl_ra(
						first, sprout::next(first, pivot), pred,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		find_if_not(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? last
				: sprout::detail::find_if_not_impl_ra(first, last, pred, sprout::distance(first, last) / 2, first)
				;
		}

		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		find_if_not_impl_1(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return current.second || current.first == last ? current
				: n == 1 ? !pred(*current.first) ? type(current.first, true) : type(sprout::next(current.first), false)
				: sprout::detail::find_if_not_impl_1(
					sprout::detail::find_if_not_impl_1(
						current,
						last, pred, n / 2
						),
					last, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		find_if_not_impl(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.second || current.first == last ? current
				: sprout::detail::find_if_not_impl(
					sprout::detail::find_if_not_impl_1(
						current,
						last, pred, n
						),
					last, pred, n * 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR InputIterator
		find_if_not(
			InputIterator first, InputIterator last, Predicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return sprout::detail::find_if_not_impl(type(first, false), last, pred, 1).first;
		}
	}	// namespace detail

	// 25.2.5 Find
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR InputIterator
	find_if_not(InputIterator first, InputIterator last, Predicate pred) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::find_if_not(first, last, pred, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_IF_NOT_HPP
