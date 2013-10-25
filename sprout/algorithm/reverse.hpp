/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_REVERSE_HPP
#define SPROUT_ALGORITHM_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/iter_swap.hpp>

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

#include <sprout/algorithm/fixed/reverse.hpp>
#include <sprout/algorithm/fit/reverse.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_REVERSE_HPP
