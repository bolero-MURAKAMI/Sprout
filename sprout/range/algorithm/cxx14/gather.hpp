/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_GATHER_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_GATHER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/gather.hpp>

namespace sprout {
	namespace range {
		//
		// gather
		//
		template<typename BidirectionalRange, typename Predicate>
		inline SPROUT_CXX14_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<BidirectionalRange>::type,
			typename sprout::range::range_return<BidirectionalRange>::type
		>
		gather(BidirectionalRange&& rng, typename sprout::container_traits<typename::std::remove_reference<BidirectionalRange>::type>::iterator pivot, Predicate pred) {
			return sprout::gather(sprout::begin(SPROUT_FORWARD(BidirectionalRange, rng)), sprout::end(SPROUT_FORWARD(BidirectionalRange, rng)), pivot, pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_GATHER_HPP
