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
#include "./find_end.cpp"
#include "./find_first_of.cpp"
#include "./adjacent_find.cpp"
#include "./count.cpp"
#include "./count_if.cpp"
#include "./mismatch.cpp"
#include "./equal.cpp"
#include "./is_permutation.cpp"
#include "./search.cpp"
#include "./search_n.cpp"
#include "./is_partitioned.cpp"
#include "./partition_point.cpp"
#include "./is_sorted.cpp"
#include "./is_sorted_until.cpp"
#include "./lower_bound.cpp"
#include "./upper_bound.cpp"
#include "./equal_range.cpp"
#include "./binary_search.cpp"
#include "./includes.cpp"

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
		testspr::algorithm_find_end_test();
		testspr::algorithm_find_first_of_test();
		testspr::algorithm_adjacent_find_test();
		testspr::algorithm_count_test();
		testspr::algorithm_count_if_test();
		testspr::algorithm_mismatch_test();
		testspr::algorithm_equal_test();
		testspr::algorithm_is_permutation_test();
		testspr::algorithm_search_test();
		testspr::algorithm_search_n_test();
		testspr::algorithm_is_partitioned_test();
		testspr::algorithm_partition_point_test();
		testspr::algorithm_is_sorted_test();
		testspr::algorithm_is_sorted_until_test();
		testspr::algorithm_lower_bound_test();
		testspr::algorithm_upper_bound_test();
		testspr::algorithm_equal_range_test();
		testspr::algorithm_binary_search_test();
		testspr::algorithm_includes_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_non_modifying_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
