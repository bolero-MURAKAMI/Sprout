/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_ITER_SWAP_HPP
#define SPROUT_ALGORITHM_CXX14_ITER_SWAP_HPP

#include <sprout/config.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// 25.3.3 swap
	//
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CXX14_CONSTEXPR void
	iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
		sprout::swap(*a, *b);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_ITER_SWAP_HPP
