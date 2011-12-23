#ifndef TESTSPR_SPROUT_RANDOM_TAUS88_HPP
#define TESTSPR_SPROUT_RANDOM_TAUS88_HPP

#include <sprout/random/taus88.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_taus88_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::taus88>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_TAUS88_HPP
