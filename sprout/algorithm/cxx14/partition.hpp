/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_PARTITION_HPP
#define SPROUT_ALGORITHM_CXX14_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/algorithm/find_if_not.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>

namespace sprout {
	//
	// 25.3.13 Partitions
	//
	template<typename ForwardIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	partition(ForwardIterator first, ForwardIterator last, Predicate pred) {
		first = sprout::find_if_not(first, last, pred);
		ForwardIterator it = sprout::find_if(first, last, pred);
		while (it != last) {
			sprout::iter_swap(first, it);
			first = sprout::find_if_not(first, last, pred);
			it = sprout::find_if(it, last, pred);
		}
		return first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_PARTITION_HPP
