/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_BOGO_SORT_HPP
#define SPROUT_ALGORITHM_CXX14_BOGO_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/is_sorted.hpp>
#include <sprout/algorithm/cxx14/shuffle.hpp>

namespace sprout {
	//
	// bogo_sort
	//
	template<typename RandomAccessIterator, typename UniformRandomNumberGenerator>
	inline SPROUT_CXX14_CONSTEXPR void
	bogo_sort(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g) {
		while (!sprout::is_sorted(first, last)) {
			sprout::shuffle(first, last, SPROUT_FORWARD(UniformRandomNumberGenerator, g));
		}
	}
	template<typename RandomAccessIterator, typename UniformRandomNumberGenerator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	bogo_sort(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g, Compare comp) {
		while (!sprout::is_sorted(first, last, comp)) {
			sprout::shuffle(first, last, SPROUT_FORWARD(UniformRandomNumberGenerator, g));
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_BOGO_SORT_HPP
