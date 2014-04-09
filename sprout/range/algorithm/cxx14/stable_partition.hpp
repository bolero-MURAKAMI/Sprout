/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_STABLE_PARTITION_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/stable_partition.hpp>

namespace sprout {
	namespace range {
		//
		// stable_partition
		//
		template<typename BidirectionalRange, typename Predicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<BidirectionalRange>::type
		stable_partition(BidirectionalRange&& rng, Predicate pred) {
			return sprout::range::range_return<BidirectionalRange>::pack(
				sprout::stable_partition(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)), pred),
				SPROUT_FORWARD(BidirectionalRange, rng)
				);
		}

		template<sprout::range::range_return_value RetV, typename BidirectionalRange, typename Predicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<BidirectionalRange, RetV>::type
		stable_partition(BidirectionalRange&& rng, Predicate pred) {
			return sprout::range::range_return<BidirectionalRange, RetV>::pack(
				sprout::stable_partition(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)), pred),
				SPROUT_FORWARD(BidirectionalRange, rng)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_STABLE_PARTITION_HPP
