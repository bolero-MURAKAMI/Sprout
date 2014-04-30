/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_SHUFFLE_HPP
#define SPROUT_ALGORITHM_CXX14_SHUFFLE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
	//
	// 25.3.12 Random shuffle
	//
	template<typename RandomAccessIterator, typename UniformRandomNumberGenerator>
	inline SPROUT_CXX14_CONSTEXPR void
	shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g) {
		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
		typedef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<std::ptrdiff_t> distribution_type;
		typedef typename distribution_type::param_type param_type;
		difference_type d = last - first;
		if (d > 1) {
			distribution_type dist;
			for (--last, --d; first < last; ++first, --d) {
				difference_type i = dist(g, param_type(0, d));
				if (i != difference_type(0)) {
					sprout::iter_swap(first, first + i);
				}
			}
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_SHUFFLE_HPP
