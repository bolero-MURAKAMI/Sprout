/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_STABLE_SORT_HPP
#define SPROUT_ALGORITHM_CXX14_STABLE_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/insertion_sort.hpp>
#include <sprout/algorithm/cxx14/inplace_merge.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		inplace_stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			if (last - first < 15) {
				sprout::detail::insertion_sort(first, last, comp);
				return;
			}
			RandomAccessIterator middle = first + (last - first) / 2;
			sprout::detail::inplace_stable_sort(first, middle, comp);
			sprout::detail::inplace_stable_sort(middle, last, comp);
			sprout::detail::inplace_merge(first, middle, last, middle - first, last - middle, comp);
		}
	}	// namespace detail
	//
	// 25.4.1.2 stable_sort
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		sprout::detail::inplace_stable_sort(first, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	stable_sort(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::stable_sort(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_STABLE_SORT_HPP
