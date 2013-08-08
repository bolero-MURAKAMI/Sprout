/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
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
		inline SPROUT_CONSTEXPR InputIterator2
		includes_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return first2 == last2 ? first2
				: pivot == 0 ? (!comp(*first1, *first2) && !comp(*first2, *first1) ? sprout::next(first2) : first2)
				: sprout::detail::includes_impl_ra(
					sprout::next(first1, pivot), last1,
					sprout::detail::includes_impl_ra(
						first1, sprout::next(first1, pivot),
						first2,
						last2, comp,
						pivot / 2
						),
					last2, comp,
					(sprout::distance(first1, last1) - pivot) / 2
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
					first1, last1, first2, last2, comp,
					sprout::distance(first1, last1) / 2
					)
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
				: n == 1 ? !comp(*current.first, *current.second) && !comp(*current.second, *current.first)
					? type(sprout::next(current.first), sprout::next(current.second))
					: type(sprout::next(current.first), current.second)
				: sprout::detail::includes_impl_1(
					sprout::detail::includes_impl_1(
						current,
						last1, last2, comp, n / 2
						),
					last1, last2, comp, n - n / 2
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
