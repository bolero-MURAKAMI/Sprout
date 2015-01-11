/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_MODIFYIING_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MODIFYIING_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_MODIFYIING_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./copy.cpp"
#include "./copy_n.cpp"
#include "./copy_if.cpp"
#include "./copy_backward.cpp"
#include "./transform.cpp"
#include "./replace.cpp"
#include "./replace_if.cpp"
#include "./replace_copy.cpp"
#include "./replace_copy_if.cpp"
#include "./fill.cpp"
#include "./fill_n.cpp"
#include "./generate.cpp"
#include "./generate_n.cpp"
#include "./unfold.cpp"
#include "./unfold_n.cpp"
#include "./recurrence.cpp"
#include "./recurrence_n.cpp"
#include "./remove.cpp"
#include "./remove_if.cpp"
#include "./remove_copy.cpp"
#include "./remove_copy_if.cpp"
#include "./unique.cpp"
#include "./unique_copy.cpp"
#include "./reverse.cpp"
#include "./reverse_copy.cpp"
#include "./rotate.cpp"
#include "./rotate_copy.cpp"
#include "./shuffle.cpp"
#include "./shuffle_result.cpp"
#include "./partition.cpp"
#include "./partition_copy.cpp"
#include "./stable_partition.cpp"
#include "./stable_partition_copy.cpp"
#include "./sort.cpp"
#include "./stable_sort.cpp"
#include "./partial_sort.cpp"
#include "./nth_element.cpp"
#include "./merge.cpp"
#include "./inplace_merge.cpp"
#include "./set_union.cpp"
#include "./set_intersection.cpp"
#include "./set_difference.cpp"
#include "./set_symmetric_difference.cpp"
#include "./push_heap.cpp"
#include "./pop_heap.cpp"
#include "./make_heap.cpp"
#include "./make_partial_heap.cpp"
#include "./sort_heap.cpp"
#include "./next_permutation.cpp"
#include "./prev_permutation.cpp"
#include "./copy_while.cpp"
#include "./copy_until.cpp"
#include "./clamp_range_copy.cpp"
#include "./clamp_range.cpp"
#include "./swap_element.cpp"
#include "./swap_element_copy.cpp"
#include "./random_swap.cpp"
#include "./random_swap_result.cpp"
#ifndef TESTSPR_CONFIG_DISABLE_MONKEY_SORT_TEST
#	include "./bogo_sort.cpp"
#	include "./bogo_sort_result.cpp"
#	include "./bozo_sort.cpp"
#	include "./bozo_sort_result.cpp"
#endif

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_MODIFYIING_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void algorithm_modifying_test() {
		testspr::algorithm_copy_test();
		testspr::algorithm_copy_n_test();
		testspr::algorithm_copy_if_test();
		testspr::algorithm_copy_backward_test();
		testspr::algorithm_transform_test();
		testspr::algorithm_replace_test();
		testspr::algorithm_replace_if_test();
		testspr::algorithm_replace_copy_test();
		testspr::algorithm_replace_copy_if_test();
		testspr::algorithm_generate_test();
		testspr::algorithm_generate_n_test();
		testspr::algorithm_fill_test();
		testspr::algorithm_fill_n_test();
		testspr::algorithm_unfold_test();
		testspr::algorithm_unfold_n_test();
		testspr::algorithm_recurrence_test();
		testspr::algorithm_recurrence_n_test();
		testspr::algorithm_remove_test();
		testspr::algorithm_remove_if_test();
		testspr::algorithm_remove_copy_test();
		testspr::algorithm_remove_copy_if_test();
		testspr::algorithm_unique_test();
		testspr::algorithm_unique_copy_test();
		testspr::algorithm_reverse_test();
		testspr::algorithm_reverse_copy_test();
		testspr::algorithm_rotate_test();
		testspr::algorithm_rotate_copy_test();
		testspr::algorithm_shuffle_test();
		testspr::algorithm_shuffle_result_test();
		testspr::algorithm_partition_test();
		testspr::algorithm_partition_copy_test();
		testspr::algorithm_stable_partition_test();
		testspr::algorithm_stable_partition_copy_test();
		testspr::algorithm_sort_test();
		testspr::algorithm_stable_sort_test();
		testspr::algorithm_partial_sort_test();
		testspr::algorithm_nth_element_test();
		testspr::algorithm_merge_test();
		testspr::algorithm_inplace_merge_test();
		testspr::algorithm_set_union_test();
		testspr::algorithm_set_intersection_test();
		testspr::algorithm_set_difference_test();
		testspr::algorithm_set_symmetric_difference_test();
		testspr::algorithm_push_heap_test();
		testspr::algorithm_pop_heap_test();
		testspr::algorithm_make_heap_test();
		testspr::algorithm_make_partial_heap_test();
		testspr::algorithm_sort_heap_test();
		testspr::algorithm_next_permutation_test();
		testspr::algorithm_prev_permutation_test();
		testspr::algorithm_copy_while_test();
		testspr::algorithm_copy_until_test();
		testspr::algorithm_clamp_range_copy_test();
		testspr::algorithm_clamp_range_test();
		testspr::algorithm_swap_element_test();
		testspr::algorithm_swap_element_copy_test();
		testspr::algorithm_random_swap_test();
		testspr::algorithm_random_swap_result_test();
#ifndef TESTSPR_CONFIG_DISABLE_MONKEY_SORT_TEST
		testspr::algorithm_bogo_sort_test();
		testspr::algorithm_bogo_sort_result_test();
		testspr::algorithm_bozo_sort_test();
		testspr::algorithm_bozo_sort_result_test();
#endif
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_modifying_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MODIFYIING_CPP
