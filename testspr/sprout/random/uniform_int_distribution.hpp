#ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define TESTSPR_SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

#include <sprout/random/uniform_int_distribution.hpp>
#include <testspr/sprout/random/distribution_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_uniform_int_distribution_test() {
		using namespace sprout;

		testspr::random_distribution_test_generic<sprout::random::uniform_int_distribution<> >();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
