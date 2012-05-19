#ifndef SPROUT_LIBS_RANDOM_TEST_UNIFORM_SMALLINT_CPP
#define SPROUT_LIBS_RANDOM_TEST_UNIFORM_SMALLINT_CPP

#include <sprout/random/uniform_smallint.hpp>
#include "./distribution_generic.hpp"
#include <testspr/tools.hpp>

namespace testspr {
	void random_uniform_smallint_test() {
		using namespace sprout;

		testspr::random_distribution_test_generic<sprout::random::uniform_smallint<> >();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_uniform_smallint_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_UNIFORM_SMALLINT_CPP
