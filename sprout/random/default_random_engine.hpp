/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_DEFAULT_RANDOM_ENGINE_HPP
#define SPROUT_RANDOM_DEFAULT_RANDOM_ENGINE_HPP

#include <sprout/config.hpp>
#include <sprout/random/linear_congruential.hpp>

namespace sprout {
	namespace random {
		//
		// default_random_engine
		//
		typedef sprout::random::minstd_rand0 default_random_engine;
	}	// namespace random

	using sprout::random::default_random_engine;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DEFAULT_RANDOM_ENGINE_HPP
