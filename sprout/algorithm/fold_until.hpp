/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FOLD_UNTIL_HPP
#define SPROUT_ALGORITHM_FOLD_UNTIL_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename T, typename BinaryOperation, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		fold_until_impl_1(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, T> type;
			return current.first == last || pred(current.second) ? current
				: n == 1 ? type(sprout::next(current.first), binary_op(current.second, *current.first))
				: sprout::detail::fold_until_impl_1(
					sprout::detail::fold_until_impl_1(
						current,
						last, binary_op, pred, n / 2
						),
					last, binary_op, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T, typename BinaryOperation, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		fold_until_impl(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.first == last || pred(current.second) ? current
				: sprout::detail::fold_until_impl(
					sprout::detail::fold_until_impl_1(
						current,
						last, binary_op, pred, n
						),
					last, binary_op, pred, n * 2
					)
				;
		}
	}	// namespace detail

	//
	// fold_until
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T, typename BinaryOperation, typename Predicate>
	inline SPROUT_CONSTEXPR T
	fold_until(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, Predicate pred) {
		typedef sprout::pair<InputIterator, T> type;
		return sprout::detail::fold_until_impl(type(first, init), last, binary_op, pred, 1).second;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FOLD_UNTIL_HPP
