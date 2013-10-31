/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_RANDOM_SHUFFLE_HPP
#define SPROUT_CXX14_ALGORITHM_RANDOM_SHUFFLE_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>

namespace sprout {
	//
	// 25.3.12 Random shuffle
	//
	template<typename RandomAccessIterator, typename RandomNumberGenerator>
	inline SPROUT_CXX14_CONSTEXPR void
	random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator&& rand) {
		if (first == last) {
			return;
		}
		for (auto it = first + 1; it != last; ++it) {
			sprout::iter_swap(it, first + rand(it - first + 1));
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_RANDOM_SHUFFLE_HPP
