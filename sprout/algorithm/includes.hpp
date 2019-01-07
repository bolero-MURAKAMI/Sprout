/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_INCLUDES_HPP
#define SPROUT_ALGORITHM_INCLUDES_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator2, bool>
		includes_impl_ra(
			RandomAccessIterator1 first1,
			sprout::pair<InputIterator2, bool> current,
			InputIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type len
			)
		{
			typedef sprout::pair<InputIterator2, bool> type;
			return current.second || current.first == last2 ? current
				: len == 1 ? comp(*current.first, *first1)
					? type(current.first, true)
					: type(comp(*first1, *current.first) ? current.first : sprout::next(current.first), false)
				: sprout::detail::includes_impl_ra(
					sprout::next(first1, len / 2),
					sprout::detail::includes_impl_ra(
						first1,
						current,
						last2, comp,
						len / 2
						),
					last2, comp,
					len - len / 2
					)
				;
		}
		template<typename RandomAccessIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			bool
		>::type
		includes(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? first2 == last2
				: sprout::detail::includes_impl_ra(
					first1,
					sprout::pair<InputIterator2, bool>(first2, false),
					last2, comp,
					sprout::distance(first1, last1)
					).first
					== last2
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		includes_impl_1(
			sprout::pair<InputIterator1, InputIterator2> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator1, InputIterator2> type;
			return current.second == last2 || current.first == last1 ? current
				: n == 1
				? comp(*current.second, *current.first)
					? type(last1, current.second)
					: type(
						sprout::next(current.first),
						comp(*current.first, *current.second) ? current.second : sprout::next(current.second)
						)
				: sprout::detail::includes_impl_1(
					sprout::detail::includes_impl_1(
						current,
						last1, last2, comp, n / 2
						),
					last1, last2, comp, n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		includes_impl(
			sprout::pair<InputIterator1, InputIterator2> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return current.second == last2 || current.first == last1 ? current
				: sprout::detail::includes_impl(
					sprout::detail::includes_impl_1(
						current,
						last1, last2, comp, n
						),
					last1, last2, comp, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		includes(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator1, InputIterator2> type;
			return first2 == last2 ? true
				: sprout::detail::includes_impl(type(first1, first2), last1, last2, comp, 1).second == last2
				;
		}
	}	// namespace detail

	// 25.4.5.1 includes
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		typedef typename std::iterator_traits<InputIterator1>::iterator_category* category;
		return sprout::detail::includes(first1, last1, first2, last2, comp, category());
	}

	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return sprout::includes(
			first1, last1, first2, last2,
			sprout::less<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INCLUDES_HPP
