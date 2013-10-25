/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_STABLE_PARTITION_HPP

#include <sprout/config.hpp>


namespace sprout {
	//
	// 25.3.13 Partitions
	//
	template<typename BidirectionalIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator
	stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred); // !!!
}	// namespace sprout

#include <sprout/algorithm/fixed/stable_partition.hpp>
#include <sprout/algorithm/fit/stable_partition.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_STABLE_PARTITION_HPP
