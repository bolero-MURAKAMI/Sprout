/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_RANDOM_TEST_RANDOM_CPP
#define SPROUT_LIBS_RANDOM_TEST_RANDOM_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_RANDOM_TEST_RANDOM_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./linear_congruential.cpp"
#include "./additive_combine.cpp"
#include "./shuffle_order.cpp"
#include "./inversive_congruential.cpp"
#include "./taus88.cpp"
//#include "./mersenne_twister.cpp"
#include "./uniform_smallint.cpp"
#include "./uniform_int_distribution.cpp"
#include "./uniform_01.cpp"
#include "./uniform_real_distribution.cpp"
#include "./bernoulli_distribution.cpp"
#include "./binomial_distribution.cpp"
#include "./geometric_distribution.cpp"
#include "./poisson_distribution.cpp"
#include "./normal_distribution.cpp"
#include <testspr/tools.hpp>

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_RANDOM_TEST_RANDOM_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

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
		testspr::random_poisson_distribution_test();
		testspr::random_normal_distribution_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_RANDOM_CPP
