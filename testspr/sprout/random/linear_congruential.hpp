#ifndef TESTSPR_SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define TESTSPR_SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <sprout/random/linear_congruential.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_linear_congruential_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::minstd_rand0>();
		testspr::random_engine_test_generic<sprout::random::minstd_rand>();
		testspr::random_engine_test_generic<sprout::random::rand48>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP
