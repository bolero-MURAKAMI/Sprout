/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./all_of.cpp"
#include "./all_of_equal.cpp"
#include "./any_of.cpp"
#include "./any_of_equal.cpp"
#include "./none_of.cpp"
#include "./none_of_equal.cpp"
#include "./one_of.cpp"
#include "./one_of_equal.cpp"
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
#include "./is_increasing.cpp"
#include "./is_decreasing.cpp"
#include "./is_strictly_increasing.cpp"
#include "./is_strictly_decreasing.cpp"
#include "./lower_bound.cpp"
#include "./upper_bound.cpp"
#include "./equal_range.cpp"
#include "./binary_search.cpp"
#include "./includes.cpp"
#include "./is_heap.cpp"
#include "./is_heap_until.cpp"
#include "./min.cpp"
#include "./max.cpp"
#include "./minmax.cpp"
#include "./min_element.cpp"
#include "./max_element.cpp"
#include "./minmax_element.cpp"
#include "./lexicographical_compare.cpp"
#include "./tristate_lexicographical_compare.cpp"
#include "./clamp.cpp"

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
		testspr::algorithm_is_heap_test();
		testspr::algorithm_is_heap_until_test();
		testspr::algorithm_min_test();
		testspr::algorithm_max_test();
		testspr::algorithm_minmax_test();
		testspr::algorithm_min_element_test();
		testspr::algorithm_max_element_test();
		testspr::algorithm_minmax_element_test();
		testspr::algorithm_lexicographical_compare_test();
		testspr::algorithm_all_of_equal_test();
		testspr::algorithm_any_of_equal_test();
		testspr::algorithm_none_of_equal_test();
		testspr::algorithm_one_of_equal_test();
		testspr::algorithm_tristate_lexicographical_compare_test();
		testspr::algorithm_is_increasing_test();
		testspr::algorithm_is_decreasing_test();
		testspr::algorithm_is_strictly_increasing_test();
		testspr::algorithm_is_strictly_decreasing_test();
		testspr::algorithm_clamp_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_non_modifying_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NON_MODIFYIING_CPP
