/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP

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
		any_of_equal_impl_ra(
			RandomAccessIterator const& first, RandomAccessIterator const& last, T const& value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? *first == value
				: sprout::detail::any_of_equal_impl_ra(
					first, sprout::next(first, pivot), value,
					pivot / 2
					)
					|| sprout::detail::any_of_equal_impl_ra(
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
		any_of_equal(
			RandomAccessIterator const& first, RandomAccessIterator const& last, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? false
				: sprout::detail::any_of_equal_impl_ra(first, last, value, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		any_of_equal_impl_1(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator const& last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return current.second || current.first == last ? current
				: n == 1 ? *current.first == value ? type(current.first, true) : type(sprout::next(current.first), false)
				: sprout::detail::any_of_equal_impl_1(
					sprout::detail::any_of_equal_impl_1(
						current,
						last, value, n / 2
						),
					last, value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		any_of_equal_impl(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator const& last, T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.second || current.first == last ? current
				: sprout::detail::any_of_equal_impl(
					sprout::detail::any_of_equal_impl_1(
						current,
						last, value, n
						),
					last, value, n * 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		any_of_equal(
			InputIterator const& first, InputIterator const& last, T const& value,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return sprout::detail::any_of_equal_impl(type(first, false), last, value, 1).second;
		}
	}	// namespace detail

	//
	// any_of_equal
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	any_of_equal(InputIterator first, InputIterator last, T const& value) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::any_of_equal(first, last, value, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP
