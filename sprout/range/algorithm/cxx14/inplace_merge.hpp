/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_IMPLACE_MERGE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_IMPLACE_MERGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/inplace_merge.hpp>

namespace sprout {
	namespace range {
		//
		// inplace_merge
		//
		template<typename BidirectionalRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		inplace_merge(BidirectionalRange&& rng, typename sprout::container_traits<typename::std::remove_reference<BidirectionalRange>::type>::iterator middle, Compare comp) {
			sprout::inplace_merge(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), middle, sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)), comp);
		}

		template<typename BidirectionalRange>
		inline SPROUT_CXX14_CONSTEXPR void
		inplace_merge(BidirectionalRange&& rng, typename sprout::container_traits<typename::std::remove_reference<BidirectionalRange>::type>::iterator middle) {
			sprout::inplace_merge(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), middle, sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_IMPLACE_MERGE_HPP
