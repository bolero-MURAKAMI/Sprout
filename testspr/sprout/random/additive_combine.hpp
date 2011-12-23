#ifndef TESTSPR_SPROUT_RANDOM_ADDITIVE_COMBINE_HPP
#define TESTSPR_SPROUT_RANDOM_ADDITIVE_COMBINE_HPP

#include <sprout/random/additive_combine.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_additive_combine_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::ecuyer1988>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_ADDITIVE_COMBINE_HPP
