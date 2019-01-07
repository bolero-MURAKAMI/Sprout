/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_TRANSFORM_REDUCE_HPP
#define SPROUT_NUMERIC_TRANSFORM_REDUCE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/plus.hpp>
#include <sprout/functional/multiplies.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		transform_reduce_ra(
			RandomAccessIterator1 const& first1, RandomAccessIterator1 const& last1, RandomAccessIterator2 const& first2,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, T const& init
			)
		{
			return pivot == 0 ? binary_op1(init, binary_op2(*first1, *first2))
				: sprout::detail::transform_reduce_ra(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), binary_op1, binary_op2,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::transform_reduce_ra(
						first1, sprout::next(first1, pivot), first2, binary_op1, binary_op2,
						pivot / 2,
						init
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			T
		>::type
		transform_reduce(
			RandomAccessIterator1 const& first1, RandomAccessIterator1 const& last1, RandomAccessIterator2 const& first2,
			T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? init
				: sprout::detail::transform_reduce_ra(
					first1, last1, first2, binary_op1, binary_op2,
					sprout::distance(first1, last1) / 2,
					init
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR sprout::tuple<InputIterator1, InputIterator2, T>
		transform_reduce_impl_1(
			sprout::tuple<InputIterator1, InputIterator2, T> const& current,
			InputIterator1 const& last1, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuple<InputIterator1, InputIterator2, T> type;
			return sprout::get<0>(current) == last1 ? current
				: n == 1 ? type(
					sprout::next(sprout::get<0>(current)), sprout::next(sprout::get<1>(current)),
					binary_op1(sprout::get<2>(current), binary_op2(*sprout::get<0>(current), *sprout::get<1>(current)))
					)
				: sprout::detail::transform_reduce_impl_1(
					sprout::detail::transform_reduce_impl_1(
						current,
						last1, binary_op1, binary_op2, n / 2
						),
					last1, binary_op1, binary_op2, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR sprout::tuple<InputIterator1, InputIterator2, T>
		transform_reduce_impl(
			sprout::tuple<InputIterator1, InputIterator2, T> const& current,
			InputIterator1 const& last1, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::get<0>(current) == last1 ? current
				: sprout::detail::transform_reduce_impl(
					sprout::detail::transform_reduce_impl_1(
						current,
						last1, binary_op1, binary_op2, n
						),
					last1, binary_op1, binary_op2, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		transform_reduce(
			InputIterator1 const& first1, InputIterator1 const& last1, InputIterator2 const& first2,
			T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuple<InputIterator1, InputIterator2, T> type;
			return sprout::get<2>(sprout::detail::transform_reduce_impl(type(first1, first2, init), last1, binary_op1, binary_op2, 1));
		}
	}	// namespace detail

	//
	// transform_reduce
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
	inline SPROUT_CONSTEXPR T
	transform_reduce(
		InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2
		)
	{
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::transform_reduce(first1, last1, first2, init, binary_op1, binary_op2, category());
	}

	template<typename InputIterator1, typename InputIterator2, typename T>
	inline SPROUT_CONSTEXPR T
	transform_reduce(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::transform_reduce(first1, last1, first2, init, sprout::plus<>(), sprout::multiplies<>(), category());
	}

	namespace detail {
		template<typename RandomAccessIterator, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR T
		transform_reduce_ra(
			RandomAccessIterator const& first, RandomAccessIterator const& last, BinaryOperation binary_op, UnaryOperation unary_op,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, T const& init
			)
		{
			return pivot == 0 ? binary_op(init, unary_op(*first))
				: sprout::detail::transform_reduce_ra(
					sprout::next(first, pivot), last, binary_op, unary_op,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::transform_reduce_ra(
						first, sprout::next(first, pivot), binary_op, unary_op,
						pivot / 2,
						init
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			T
		>::type
		transform_reduce(
			RandomAccessIterator const& first, RandomAccessIterator const& last, T init, BinaryOperation binary_op, UnaryOperation unary_op,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? init
				: sprout::detail::transform_reduce_ra(
					first, last, binary_op, unary_op,
					sprout::distance(first, last) / 2,
					init
					)
				;
		}

		template<typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		transform_reduce_impl_1(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, UnaryOperation unary_op,
			typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, T> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), binary_op(current.second, unary_op(*current.first)))
				: sprout::detail::transform_reduce_impl_1(
					sprout::detail::transform_reduce_impl_1(
						current,
						last, binary_op, unary_op, n / 2
						),
					last, binary_op, unary_op, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, T>
		transform_reduce_impl(
			sprout::pair<InputIterator, T> const& current,
			InputIterator const& last, BinaryOperation binary_op, UnaryOperation unary_op,
			typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return current.first == last ? current
				: sprout::detail::transform_reduce_impl(
					sprout::detail::transform_reduce_impl_1(
						current,
						last, binary_op, unary_op, n
						),
					last, binary_op, unary_op, n * 2
					)
				;
		}
		template<typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR T
		transform_reduce(
			InputIterator const& first, InputIterator const& last, T init, BinaryOperation binary_op, UnaryOperation unary_op,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, T> type;
			return sprout::detail::transform_reduce_impl(type(first, init), last, binary_op, unary_op, 1).second;
		}
	}	// namespace detail

	//
	// transform_reduce
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
	inline SPROUT_CONSTEXPR T
	transform_reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, UnaryOperation unary_op) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::transform_reduce(first, last, init, binary_op, unary_op, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_TRANSFORM_REDUCE_HPP
