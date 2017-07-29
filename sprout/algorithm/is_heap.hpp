/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_IS_HEAP_HPP
#define SPROUT_ALGORITHM_IS_HEAP_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/is_heap_until.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {

	// 25.4.6.5 is_heap
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CONSTEXPR bool
	is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		return sprout::is_heap_until(first, last, comp) == last;
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CONSTEXPR bool
	is_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return sprout::is_heap(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_HEAP_HPP
