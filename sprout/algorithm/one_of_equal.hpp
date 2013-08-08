/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		one_of_equal_impl_ra_1(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? !(*first == value)
				: sprout::detail::one_of_equal_impl_ra_1(
					first, sprout::next(first, pivot), value,
					pivot / 2
					)
					&& sprout::detail::one_of_equal_impl_ra_1(
						sprout::next(first, pivot), last, value,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		one_of_equal_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? *first == value
				: sprout::detail::one_of_equal_impl_ra(
					first, sprout::next(first, pivot), value,
					pivot / 2
					)
					? sprout::detail::one_of_equal_impl_ra_1(
						sprout::next(first, pivot), last, value,
						(sprout::distance(first, last) - pivot) / 2
						)
					: sprout::detail::one_of_equal_impl_ra(
						sprout::next(first, pivot), last, value,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			bool
		>::type
		one_of_equal(
			RandomAccessIterator first, RandomAccessIterator last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? true
				: sprout::detail::one_of_equal_impl_ra(first, last, value, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		one_of_equal_impl_1(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.second > 1 || current.first == last ? current
				: n == 1 ? current.second == 0
					? type(sprout::next(current.first), *current.first == value ? 1 : 0)
					: !(*current.first == value) ? type(sprout::next(current.first), 1) : type(current.first, 2)
				: sprout::detail::one_of_equal_impl_1(
					sprout::detail::one_of_equal_impl_1(
						current,
						last, value, n / 2
						),
					last, value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		one_of_equal_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.second > 1 || current.first == last ? current
				: sprout::detail::one_of_equal_impl(
					sprout::detail::one_of_equal_impl_1(
						current,
						last, value, n
						),
					last, value, n * 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		one_of_equal(
			InputIterator first, InputIterator last, T const& value,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::detail::one_of_equal_impl(type(first, 0), last, value, 1).second == 1;
		}
	}	// namespace detail

	//
	// one_of_equal
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	one_of_equal(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::one_of_equal(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP
