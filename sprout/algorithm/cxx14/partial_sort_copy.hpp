/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP
#define SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/heap_tool.hpp>
#include <sprout/algorithm/cxx14/make_heap.hpp>
#include <sprout/algorithm/cxx14/sort_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename RandomAccessIterator, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR RandomAccessIterator
		partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			RandomAccessIterator r = result_first;
			if (r != result_last) {
				difference_type len = 0;
				for (; first != last && r != result_last; ++first, ++r, ++len) {
					*r = *first;
				}
				sprout::detail::make_heap<Compare>(result_first, r, comp);
				for (; first != last; ++first) {
					if (comp(*first, *result_first)) {
						*result_first = *first;
						sprout::detail::push_heap_front<Compare>(result_first, r, comp, len);
					}
				}
				sprout::detail::sort_heap<Compare>(result_first, r, comp);
			}
			return r;
		}
	}	// namespace detail
	//
	// 25.4.1.4 partial_sort_copy
	//
	template<typename InputIterator, typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR RandomAccessIterator
	partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		return sprout::detail::partial_sort_copy<compare_ref>(first, last, result_first, result_last, comp);
	}

	template<typename InputIterator, typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR RandomAccessIterator
	partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last) {
		return sprout::partial_sort_copy(
			first, last, result_first, result_last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP
