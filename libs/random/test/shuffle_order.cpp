/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_RANDOM_TEST_SHUFFLE_ORDER_CPP
#define SPROUT_LIBS_RANDOM_TEST_SHUFFLE_ORDER_CPP

#include <sprout/random/shuffle_order.hpp>
#include "./engine_generic.hpp"
#include <testspr/tools.hpp>

namespace testspr {
	void random_shuffle_order_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::knuth_b>();
		testspr::random_engine_test_generic<sprout::random::kreutzer1986>();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::random_shuffle_order_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_SHUFFLE_ORDER_CPP
