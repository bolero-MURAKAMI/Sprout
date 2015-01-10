/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_COUNT_HPP
#define SPROUT_ALGORITHM_COUNT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count_impl_ra(
			RandomAccessIterator first, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type size
			)
		{
			return size == 1 ? (*first == value ? 1 : 0)
				: sprout::detail::count_impl_ra(
					first, value,
					size / 2
					)
					+ sprout::detail::count_impl_ra(
						sprout::next(first, size / 2), value,
						size - size / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		count(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? 0
				: sprout::detail::count_impl_ra(first, value, sprout::distance(first, last))
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_impl_1(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), current.second + (*current.first == value ? 1 : 0))
				: sprout::detail::count_impl_1(
					sprout::detail::count_impl_1(
						current,
						last, value, n / 2
						),
					last, value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.first == last ? current
				: sprout::detail::count_impl(
					sprout::detail::count_impl_1(
						current,
						last, value, n
						),
					last, value, n * 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count(
			InputIterator first, InputIterator last, T const& value,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::detail::count_impl(type(first, 0), last, value, 1).second;
		}
	}	// namespace detail

	// 25.2.9 Count
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::count(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_HPP
