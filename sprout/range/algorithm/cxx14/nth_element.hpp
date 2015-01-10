/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_NTH_ELEMENT_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_NTH_ELEMENT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/nth_element.hpp>

namespace sprout {
	namespace range {
		//
		// nth_element
		//
		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		nth_element(RandomAccessRange&& rng, typename sprout::container_traits<typename::std::remove_reference<RandomAccessRange>::type>::iterator nth, Compare comp) {
			sprout::nth_element(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), nth, sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)), comp);
		}

		template<typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR void
		nth_element(RandomAccessRange&& rng, typename sprout::container_traits<typename::std::remove_reference<RandomAccessRange>::type>::iterator nth) {
			sprout::nth_element(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), nth, sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_NTH_ELEMENT_HPP
