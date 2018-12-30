/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_REVERSE_HPP
#define SPROUT_ALGORITHM_CXX14_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>

namespace sprout {
	//
	// 25.3.10 Reverse
	//
	template<typename BidirectionalIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	reverse(BidirectionalIterator first, BidirectionalIterator last) {
		for (; first != last && first != --last; ++first) {
			sprout::iter_swap(first, last);
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_REVERSE_HPP
