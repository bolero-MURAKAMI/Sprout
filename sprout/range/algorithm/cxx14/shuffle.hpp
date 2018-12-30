/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_SHUFFLE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_SHUFFLE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/shuffle.hpp>

namespace sprout {
	namespace range {
		//
		// shuffle
		//
		template<typename RandomAccessRange, typename UniformRandomNumberGenerator>
		inline SPROUT_CXX14_CONSTEXPR void
		shuffle(RandomAccessRange&& rng, UniformRandomNumberGenerator&& g) {
			sprout::shuffle(
				sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)),
				SPROUT_FORWARD(UniformRandomNumberGenerator, g)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_SHUFFLE_HPP
