/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_RANDOM_SHUFFLE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_RANDOM_SHUFFLE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/random_shuffle.hpp>

namespace sprout {
	namespace range {
		//
		// random_shuffle
		//
		template<typename RandomAccessRange, typename RandomNumberGenerator>
		inline SPROUT_CXX14_CONSTEXPR void
		random_shuffle(RandomAccessRange&& rng, RandomNumberGenerator&& rand) {
			sprout::random_shuffle(
				sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)),
				SPROUT_FORWARD(RandomNumberGenerator, rand)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_RANDOM_SHUFFLE_HPP
