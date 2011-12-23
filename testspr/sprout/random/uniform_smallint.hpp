#ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
#define TESTSPR_SPROUT_RANDOM_UNIFORM_SMALLINT_HPP

#include <sprout/random/uniform_smallint.hpp>
#include <testspr/sprout/random/distribution_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_uniform_smallint_test() {
		using namespace sprout;

		testspr::random_distribution_test_generic<sprout::random::uniform_smallint<> >();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
