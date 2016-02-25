/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_MOVE_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_MOVE_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/move_backward.hpp>

namespace sprout {
	namespace range {
		//
		// move_backward
		//
		template<
			typename BidirectionalRange, typename BidirectionalIterator,
			typename sprout::enabler_if<sprout::is_iterator_outputable<BidirectionalIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator
		move_backward(BidirectionalRange const& rng, BidirectionalIterator result) {
			return sprout::move_backward(sprout::begin(rng), sprout::end(rng), result);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_MOVE_BACKWARD_HPP
