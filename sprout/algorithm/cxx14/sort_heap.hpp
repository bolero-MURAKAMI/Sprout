/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_SORT_HEAP_HPP
#define SPROUT_ALGORITHM_CXX14_SORT_HEAP_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/pop_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type len = last - first;
			for (difference_type len = last - first; len > 1; --last, --len) {
				sprout::detail::pop_heap<Compare>(first, last, comp, len);
			}
		}
	}	// namespace detail
	//
	// 25.4.6.4 sort_heap
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::sort_heap<compare_ref>(first, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::sort_heap(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_SORT_HEAP_HPP
