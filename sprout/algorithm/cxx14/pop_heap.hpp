/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_POP_HEAP_HPP
#define SPROUT_ALGORITHM_CXX14_POP_HEAP_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/heap_tool.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		pop_heap(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type len
			)
		{
			if (len > 1) {
				sprout::swap(*first, *--last);
				sprout::detail::push_heap_front<Compare>(first, last, comp, len - 1);
			}
		}
	}	// namespace detail
	//
	// 25.4.6.2 pop_heap
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::pop_heap<compare_ref>(first, last, comp, last - first);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::pop_heap(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_POP_HEAP_HPP
