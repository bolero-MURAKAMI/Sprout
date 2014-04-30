/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_RANDOM_SWAP_HPP
#define SPROUT_ALGORITHM_CXX14_RANDOM_SWAP_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
	//
	// random_swap
	//
	template<typename RandomAccessIterator, typename UniformRandomNumberGenerator>
	inline SPROUT_CXX14_CONSTEXPR void
	random_swap(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g) {
		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
		typedef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<std::ptrdiff_t> distribution_type;
		difference_type d = last - first;
		if (d > 1) {
			distribution_type dist(0, d);
			difference_type i = dist(g);
			difference_type j = dist(g);
			if (i != j) {
				sprout::iter_swap(first + i, first + j);
			}
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_RANDOM_SWAP_HPP
