#ifndef SPROUT_LIBS_RANDOM_TEST_UNIFORM_INT_DISTRIBUTION_CPP
#define SPROUT_LIBS_RANDOM_TEST_UNIFORM_INT_DISTRIBUTION_CPP

#include <sprout/random/uniform_int_distribution.hpp>
#include "./distribution_generic.hpp"
#include <testspr/tools.hpp>

namespace testspr {
	void random_uniform_int_distribution_test() {
		using namespace sprout;

		testspr::random_distribution_test_generic<sprout::random::uniform_int_distribution<> >();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_uniform_int_distribution_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_UNIFORM_INT_DISTRIBUTION_CPP
