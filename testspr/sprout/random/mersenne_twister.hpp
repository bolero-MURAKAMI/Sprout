#ifndef TESTSPR_SPROUT_RANDOM_MERSENNE_TWISTER_HPP
#define TESTSPR_SPROUT_RANDOM_MERSENNE_TWISTER_HPP

#include <sprout/random/mersenne_twister.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_mersenne_twister_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::mt11213b>();
		//testspr::random_engine_test_generic<sprout::random::mt19937>();
		//testspr::random_engine_test_generic<sprout::random::mt19937_64>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_MERSENNE_TWISTER_HPP
