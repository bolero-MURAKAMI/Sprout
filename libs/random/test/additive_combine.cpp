/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_RANDOM_TEST_ADDITIVE_COMBINE_CPP
#define SPROUT_LIBS_RANDOM_TEST_ADDITIVE_COMBINE_CPP

#include <sprout/random/additive_combine.hpp>
#include "./engine_generic.hpp"
#include <testspr/tools.hpp>

namespace testspr {
	void random_additive_combine_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::ecuyer1988>();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_additive_combine_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_ADDITIVE_COMBINE_CPP
