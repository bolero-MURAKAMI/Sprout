/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_SWAP_RANGES_HPP
#define SPROUT_ALGORITHM_SWAP_RANGES_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/iter_swap.hpp>

namespace sprout {
	//
	// 25.3.3 swap
	//
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator2
	swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		while (first1 != last1) {
			sprout::iter_swap(*first1++, *first2++);
		}
		return first2;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SWAP_RANGES_HPP
