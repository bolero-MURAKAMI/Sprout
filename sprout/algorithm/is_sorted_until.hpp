/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
#define SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		is_sorted_until_impl_ra(
			RandomAccessIterator const& first, RandomAccessIterator const& last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator const& found
			)
		{
			return found != first ? found
				: pivot == 0 ? (comp(*last, *first) ? first : last)
				: sprout::detail::is_sorted_until_impl_ra(
					sprout::next(first, pivot), last, comp,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::is_sorted_until_impl_ra(
						first, sprout::next(first, pivot), comp,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		is_sorted_until(
			RandomAccessIterator const& first, RandomAccessIterator const& last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last || sprout::distance(first, last) == 1 ? last
				: sprout::next(
					sprout::detail::is_sorted_until_impl_ra(
						first, sprout::next(first, sprout::distance(first, last) - 1), comp,
						(sprout::distance(first, last) - 1) / 2, first
						)
					)
				;
		}

		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		is_sorted_until_impl_1(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			ForwardIterator const& last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return current.second == last ? current
				: n == 1 ? comp(*current.second, *current.first)
					? type(current.first, last)
					: type(current.second, sprout::next(current.second))
				: sprout::detail::is_sorted_until_impl_1(
					sprout::detail::is_sorted_until_impl_1(
						current,
						last, comp, n / 2
						),
					last, comp, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		is_sorted_until_impl(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			ForwardIterator const& last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			return current.second == last ? current
				: sprout::detail::is_sorted_until_impl(
					sprout::detail::is_sorted_until_impl_1(
						current,
						last, comp, n
						),
					last, comp, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		is_sorted_until(
			ForwardIterator const& first, ForwardIterator const& last, Compare comp,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return first == last ? last
				: sprout::next(
					sprout::detail::is_sorted_until_impl(type(first, sprout::next(first)), last, comp, 1).first
					)
				;
		}
	}	// namespace detail

	// 25.4.1.5 is_sorted
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::is_sorted_until(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last) {
		return sprout::is_sorted_until(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
