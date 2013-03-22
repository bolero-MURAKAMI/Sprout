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
