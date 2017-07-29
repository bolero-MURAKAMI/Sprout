/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/partial_sort.hpp>

namespace sprout {
	namespace range {
		//
		// partial_sort
		//
		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		partial_sort(RandomAccessRange&& rng, typename sprout::container_traits<typename::std::remove_reference<RandomAccessRange>::type>::iterator middle, Compare comp) {
			sprout::partial_sort(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), middle, sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)), comp);
		}

		template<typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR void
		partial_sort(RandomAccessRange&& rng, typename sprout::container_traits<typename::std::remove_reference<RandomAccessRange>::type>::iterator middle) {
			sprout::partial_sort(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), middle, sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_HPP
