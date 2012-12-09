#ifndef SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./all_of.cpp"
#include "./any_of.cpp"
#include "./none_of.cpp"
#include "./one_of.cpp"
#include "./find.cpp"
#include "./find_if.cpp"
#include "./find_if_not.cpp"

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void algorithm_non_modifying_test() {
		testspr::algorithm_all_of_test();
		testspr::algorithm_any_of_test();
		testspr::algorithm_none_of_test();
		testspr::algorithm_one_of_test();
		testspr::algorithm_find_test();
		testspr::algorithm_find_if_test();
		testspr::algorithm_find_if_not_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_non_modifying_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
