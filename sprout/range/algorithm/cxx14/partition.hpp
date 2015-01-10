/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTITION_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/partition.hpp>

namespace sprout {
	namespace range {
		//
		// partition
		//
		template<typename ForwardRange, typename Predicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		partition(ForwardRange&& rng, Predicate pred) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::partition(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), pred),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Predicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		partition(ForwardRange&& rng, Predicate pred) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::partition(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), pred),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTITION_HPP
