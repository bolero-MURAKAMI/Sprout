/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_GATHER_HPP
#define SPROUT_ALGORITHM_CXX14_GATHER_HPP

#include <sprout/config.hpp>
#include <sprout/functional/not1.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/cxx14/stable_partition.hpp>

namespace sprout {
	//
	// gather
	//
	template<typename BidirectionalIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR sprout::pair<BidirectionalIterator, BidirectionalIterator>
	gather(BidirectionalIterator first, BidirectionalIterator last, BidirectionalIterator pivot, Predicate pred) {
		return sprout::pair<BidirectionalIterator, BidirectionalIterator>(
			sprout::stable_partition(first, pivot, sprout::not1(pred)),
			sprout::stable_partition(pivot, last, pred)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_GATHER_HPP
