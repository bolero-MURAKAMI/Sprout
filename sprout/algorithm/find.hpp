/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIND_HPP
#define SPROUT_ALGORITHM_FIND_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		find_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (*first == value ? first : last)
				: sprout::detail::find_impl_ra(
					sprout::next(first, pivot), last, value,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::find_impl_ra(
						first, sprout::next(first, pivot), value,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		find(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? last
				: sprout::detail::find_impl_ra(first, last, value, sprout::distance(first, last) / 2, first)
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		find_impl_1(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return current.second || current.first == last ? current
				: n == 1 ? *current.first == value ? type(current.first, true) : type(sprout::next(current.first), false)
				: sprout::detail::find_impl_1(
					sprout::detail::find_impl_1(
						current,
						last, value, n / 2
						),
					last, value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		find_impl(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.second || current.first == last ? current
				: sprout::detail::find_impl(
					sprout::detail::find_impl_1(
						current,
						last, value, n
						),
					last, value, n * 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		find(
			InputIterator first, InputIterator last, T const& value,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return sprout::detail::find_impl(type(first, false), last, value, 1).first;
		}
	}	// namespace detail

	// 25.2.5 Find
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR InputIterator
	find(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::find(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_HPP
