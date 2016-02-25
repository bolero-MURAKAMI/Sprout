/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_RANDOM_TEST_INVERSIVE_CONGRUENTIAL_CPP
#define SPROUT_LIBS_RANDOM_TEST_INVERSIVE_CONGRUENTIAL_CPP

#include <sprout/random/inversive_congruential.hpp>
#include "./engine_generic.hpp"
#include <testspr/tools.hpp>

namespace testspr {
	void random_inversive_congruential_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::hellekalek1995>();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_inversive_congruential_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_INVERSIVE_CONGRUENTIAL_CPP
