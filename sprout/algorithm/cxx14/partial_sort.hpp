/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_HPP
#define SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/heap_tool.hpp>
#include <sprout/algorithm/cxx14/make_heap.hpp>
#include <sprout/algorithm/cxx14/sort_heap.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			sprout::detail::make_heap<Compare>(first, middle, comp);
			difference_type len = middle - first;
			for (RandomAccessIterator i = middle; i != last; ++i) {
				if (comp(*i, *first)) {
					sprout::swap(*i, *first);
					sprout::detail::push_heap_front<Compare>(first, middle, comp, len);
				}
			}
			sprout::detail::sort_heap<Compare>(first, middle, comp);
		}
	}	// namespace detail
	//
	// 25.4.1.3 partial_sort
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::partial_sort<compare_ref>(first, middle, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
		sprout::partial_sort(
			first, middle, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_HPP
