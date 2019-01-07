/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./non_modifying.cpp"
#include "./modifying.cpp"

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void algorithm_test() {
		testspr::algorithm_non_modifying_test();
		testspr::algorithm_modifying_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
