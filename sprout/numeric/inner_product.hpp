/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_INNNER_PRODUCT_HPP
#define SPROUT_NUMERIC_INNNER_PRODUCT_HPP

#include <iterator>
#include <type_traits>
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
		inner_product_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, T init
			)
		{
			return pivot == 0 ? binary_op(init, binary_op2(*first1, *first2))
				: sprout::detail::inner_product_ra(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), binary_op1, binary_op2,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::inner_product_ra(
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
		inner_product(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, T init,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? init
				: sprout::detail::inner_product_ra(
					first1, last1, first2, binary_op1, binary_op2,
					sprout::distance(first1, last1) / 2,
					init
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, T>
		inner_product_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, T> const& current,
			InputIterator1 last1, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, T> type;
			return sprout::tuples::get<0>(current) == last1 ? current
				: n == 1 ? type(
					sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)),
					binary_op1(sprout::tuples::get<2>(current), binary_op2(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current)))
					)
				: sprout::detail::inner_product_impl_1(
					sprout::detail::inner_product_impl_1(
						current,
						last1, binary_op1, binary_op2, n / 2
						),
					last1, binary_op1, binary_op2, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, T>
		inner_product_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, T> const& current,
			InputIterator1 last1, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::tuples::get<0>(current) == last1 ? current
				: sprout::detail::inner_product_impl(
					sprout::detail::inner_product_impl_1(
						current,
						last1, binary_op1, binary_op2, n
						),
					last1, binary_op1, binary_op2, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		inner_product(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			std::input_iterator_tag*
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, T> type;
			return sprout::tuples::get<2>(sprout::detail::inner_product_impl(type(first1, first2, init), last1, binary_op1, binary_op2));
		}
	}	// namespace detail

	//
	// inner_product
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
	inline SPROUT_CONSTEXPR T
	inner_product(
		InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
		BinaryOperation1 binary_op1, BinaryOperation2 binary_op2
		)
	{
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::inner_product(first1, last1, first2, init, binary_op1, binary_op2, category());
	}

	template<typename InputIterator1, typename InputIterator2, typename T>
	inline SPROUT_CONSTEXPR T
	inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
		return sprout::inner_product(
			first1, last1, first2, init,
			sprout::plus<>(),
			sprout::multiplies<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_INNNER_PRODUCT_HPP
