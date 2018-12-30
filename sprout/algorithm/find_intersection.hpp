/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIND_INTERSECTION_HPP
#define SPROUT_ALGORITHM_FIND_INTERSECTION_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		find_intersection_impl_check(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2
			)
		{
			return sprout::tuples::get<2>(current)
				? sprout::pair<InputIterator1, InputIterator2>(
					sprout::tuples::get<0>(current),
					sprout::tuples::get<1>(current)
					)
				: sprout::pair<InputIterator1, InputIterator2>(last1, last2)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		find_intersection_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: n == 1 ? comp(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
						? type(sprout::next(sprout::tuples::get<0>(current)), sprout::tuples::get<1>(current), false)
					: comp(*sprout::tuples::get<1>(current), *sprout::tuples::get<0>(current))
						? type(sprout::tuples::get<0>(current), sprout::next(sprout::tuples::get<1>(current)), false)
					: type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
				: sprout::detail::find_intersection_impl_1(
					sprout::detail::find_intersection_impl_1(
						current,
						last1, last2, comp, n / 2
						),
					last1, last2, comp, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, bool>
		find_intersection_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, bool> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::tuples::get<2>(current) || sprout::tuples::get<0>(current) == last1 || sprout::tuples::get<1>(current) == last2 ? current
				: sprout::detail::find_intersection_impl(
					sprout::detail::find_intersection_impl_1(
						current,
						last1, last2, comp, n
						),
					last1, last2, comp, n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		find_intersection(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, bool> type;
			return sprout::detail::find_intersection_impl_check(
				sprout::detail::find_intersection_impl(type(first1, first2, false), last1, last2, comp, 1),
				last1, last2
				);
		}
	}	// namespace detail

	//
	// find_intersection
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	find_intersection(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		return sprout::detail::find_intersection(first1, last1, first2, last2, comp);
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	find_intersection(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::find_intersection(first1, last1, first2, last2, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_INTERSECTION_HPP
