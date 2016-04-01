/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_ACCUMLATE_HPP
#define SPROUT_NUMERIC_ACCUMLATE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/functional/plus.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		accumulate_ra(
			RandomAccessIterator const& first, RandomAccessIterator const& last, BinaryOperation binary_op,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, T const& init
			)
		{
			return pivot == 0 ? binary_op(init, *first)
				: sprout::detail::accumulate_ra(
					sprout::next(first, pivot), last, binary_op,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::accumulate_ra(
						first, sprout::next(first, pivot), binary_op,
						pivot / 2,
						init
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			T
		>::type
		accumulate(
			RandomAccessIterator const& first, RandomAccessIterator const& last, T init, BinaryOperation binary_op,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? init
				: sprout::detail::accumulate_ra(
					first, last, binary_op,
					sprout::distance(first, last) / 2,
					init
					)
				;
		}

		template<typename InputIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		accumulate_impl_1(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, T> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), binary_op(current.second, *current.first))
				: sprout::detail::accumulate_impl_1(
					sprout::detail::accumulate_impl_1(
						current,
						last, binary_op, n / 2
						),
					last, binary_op, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		accumulate_impl(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.first == last ? current
				: sprout::detail::accumulate_impl(
					sprout::detail::accumulate_impl_1(
						current,
						last, binary_op, n
						),
					last, binary_op, n * 2
					)
				;
		}
		template<typename InputIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		accumulate(
			InputIterator const& first, InputIterator const& last, T init, BinaryOperation binary_op,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, T> type;
			return sprout::detail::accumulate_impl(type(first, init), last, binary_op, 1).second;
		}
	}	// namespace detail

	//
	// accumulate
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T, typename BinaryOperation>
	inline SPROUT_CONSTEXPR T
	accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::accumulate(first, last, init, binary_op, category());
	}

	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR T
	accumulate(InputIterator first, InputIterator last, T init) {
		return sprout::accumulate(
			first, last, init,
			sprout::plus<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_ACCUMLATE_HPP
