/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/count.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		count_n(
			RandomAccessIterator const& first, typename std::iterator_traits<RandomAccessIterator>::difference_type n, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return sprout::count(first, sprout::next(first, n), value);
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_n_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return n == 1 ? type(sprout::next(current.first), current.second + (*current.first == value ? 1 : 0))
				: sprout::detail::count_n_impl(
					sprout::detail::count_n_impl(
						current,
						value, n / 2
						),
					value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n(
			InputIterator const& first, typename std::iterator_traits<InputIterator>::difference_type n, T const& value,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return n == 0 ? 0
				: sprout::detail::count_n_impl(type(first, 0), value, n).second
				;
		}

		//
		// count_n
		//
		//	recursion depth:
		//		O(log N)
		//
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n(InputIterator const& first, typename std::iterator_traits<InputIterator>::difference_type n, T const& value) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::count_n(first, n, value, category());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
