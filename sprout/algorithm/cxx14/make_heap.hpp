/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_MAKE_HEAP_HPP
#define SPROUT_ALGORITHM_CXX14_MAKE_HEAP_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/heap_tool.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type len = last - first;
			if (len > 1) {
				last = first;
				++last;
				for (difference_type i = 1; i < len; ++i) {
					sprout::detail::push_heap_back<Compare>(first, ++last, comp, i);
				}
			}
		}
	}	// namespace detail
	//
	// 25.4.6.3 make_heap
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::make_heap<compare_ref>(first, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	make_heap(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::make_heap(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_MAKE_HEAP_HPP
