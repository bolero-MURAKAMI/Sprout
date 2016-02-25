/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_GENERATE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/generate.hpp>

namespace sprout {
	namespace range {
		//
		// generate
		//
		template<typename ForwardRange, typename Generator>
		inline SPROUT_CXX14_CONSTEXPR void
		generate(ForwardRange&& rng, Generator gen) {
			sprout::generate(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), gen);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_GENERATE_HPP
