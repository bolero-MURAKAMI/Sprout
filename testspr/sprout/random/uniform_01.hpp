#ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_01_HPP
#define TESTSPR_SPROUT_RANDOM_UNIFORM_01_HPP

#include <sprout/random/uniform_01.hpp>
#include <testspr/sprout/random/distribution_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_uniform_01_test() {
		using namespace sprout;

		testspr::random_distribution_test_generic<sprout::random::uniform_01<> >();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_01_HPP
