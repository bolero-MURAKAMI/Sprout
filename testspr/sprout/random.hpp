#ifndef TESTSPR_SPROUT_RANDOM_HPP
#define TESTSPR_SPROUT_RANDOM_HPP

#include <testspr/sprout/random/linear_congruential.hpp>
#include <testspr/sprout/random/additive_combine.hpp>
#include <testspr/sprout/random/shuffle_order.hpp>
#include <testspr/sprout/random/inversive_congruential.hpp>
#include <testspr/sprout/random/taus88.hpp>
//#include <testspr/sprout/random/mersenne_twister.hpp>
#include <testspr/sprout/random/uniform_smallint.hpp>
#include <testspr/sprout/random/uniform_int_distribution.hpp>
#include <testspr/sprout/random/uniform_01.hpp>
#include <testspr/sprout/random/uniform_real_distribution.hpp>
#include <testspr/sprout/random/bernoulli_distribution.hpp>
#include <testspr/sprout/random/binomial_distribution.hpp>
#include <testspr/sprout/random/geometric_distribution.hpp>
#include <testspr/sprout/random/normal_distribution.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_test() {
		using namespace sprout;

		testspr::random_linear_congruential_test();
		testspr::random_additive_combine_test();
		testspr::random_shuffle_order_test();
		testspr::random_inversive_congruential_test();
		testspr::random_taus88_test();
		//testspr::random_mersenne_twister_test();
		testspr::random_uniform_smallint_test();
		testspr::random_uniform_int_distribution_test();
		testspr::random_uniform_01_test();
		testspr::random_uniform_real_distribution_test();
		testspr::random_bernoulli_distribution_test();
		testspr::random_binomial_distribution_test();
		testspr::random_geometric_distribution_test();
		testspr::random_normal_distribution_test();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_HPP
