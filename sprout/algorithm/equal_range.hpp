/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
#define SPROUT_ALGORITHM_EQUAL_RANGE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/lower_bound.hpp>
#include <sprout/algorithm/upper_bound.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename ForwardIterator, typename T, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		equal_range(
			ForwardIterator first, typename std::iterator_traits<ForwardIterator>::difference_type len,
			T const& value, Compare comp
			)
		{
			return len == 0 ? sprout::pair<ForwardIterator, ForwardIterator>(first, first)
				: comp(*sprout::next(first, len / 2), value)
					? sprout::detail::equal_range(sprout::next(first, len / 2 + 1), len - (len / 2 + 1), value, comp)
				: comp(value, *sprout::next(first, len / 2))
					? sprout::detail::equal_range(first, len / 2, value, comp)
				: sprout::pair<ForwardIterator, ForwardIterator>(
					sprout::detail::lower_bound(first, len / 2, value, comp),
					sprout::detail::upper_bound(sprout::next(first, len / 2 + 1), len - (len / 2 + 1), value, comp)
					)
				;
		}
	}	// namespace detail

	// 25.4.3.3 equal_range
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	equal_range(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return sprout::detail::equal_range(first, sprout::distance(first, last), value, comp);
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	equal_range(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::equal_range(first, last, value, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_EQUAL_RANGE_HPP
