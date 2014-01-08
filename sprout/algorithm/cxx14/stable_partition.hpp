/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_STABLE_PARTITION_HPP
#define SPROUT_CXX14_ALGORITHM_STABLE_PARTITION_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.13 Partitions
	//
	// !!! TODO: implementation
	template<typename BidirectionalIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator
	stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred);
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_STABLE_PARTITION_HPP
