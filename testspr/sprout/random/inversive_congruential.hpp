#ifndef TESTSPR_SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP
#define TESTSPR_SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

#include <sprout/random/linear_congruential.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_inversive_congruential_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::hellekalek1995>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP
