#ifndef TESTSPR_SPROUT_ALGORITHM_HPP
#define TESTSPR_SPROUT_ALGORITHM_HPP

#include <testspr/sprout/algorithm/copy.hpp>
#include <testspr/sprout/algorithm/copy_n.hpp>
#include <testspr/sprout/algorithm/copy_if.hpp>
#include <testspr/sprout/algorithm/copy_backward.hpp>
#include <testspr/sprout/algorithm/transform.hpp>
#include <testspr/sprout/algorithm/replace.hpp>
#include <testspr/sprout/algorithm/replace_if.hpp>
#include <testspr/sprout/algorithm/replace_copy.hpp>
#include <testspr/sprout/algorithm/replace_copy_if.hpp>
#include <testspr/sprout/algorithm/fill.hpp>
#include <testspr/sprout/algorithm/fill_n.hpp>
#include <testspr/sprout/algorithm/generate.hpp>
#include <testspr/sprout/algorithm/generate_n.hpp>
#include <testspr/sprout/algorithm/remove.hpp>
#include <testspr/sprout/algorithm/remove_if.hpp>
#include <testspr/sprout/algorithm/remove_copy.hpp>
#include <testspr/sprout/algorithm/remove_copy_if.hpp>
#include <testspr/sprout/algorithm/unique.hpp>
#include <testspr/sprout/algorithm/unique_copy.hpp>
#include <testspr/sprout/algorithm/reverse.hpp>
#include <testspr/sprout/algorithm/reverse_copy.hpp>
#include <testspr/sprout/algorithm/rotate.hpp>
#include <testspr/sprout/algorithm/rotate_copy.hpp>
#include <testspr/sprout/algorithm/shuffle.hpp>
#include <testspr/sprout/algorithm/shuffle_result.hpp>
#include <testspr/sprout/algorithm/partition.hpp>
#include <testspr/sprout/algorithm/partition_copy.hpp>
#include <testspr/sprout/algorithm/stable_partition.hpp>
#include <testspr/sprout/algorithm/stable_partition_copy.hpp>
#include <testspr/sprout/algorithm/sort.hpp>
#include <testspr/sprout/algorithm/stable_sort.hpp>
#include <testspr/sprout/algorithm/partial_sort.hpp>
#include <testspr/sprout/algorithm/nth_element.hpp>
#include <testspr/sprout/algorithm/merge.hpp>
#include <testspr/sprout/algorithm/inplace_merge.hpp>
#include <testspr/sprout/algorithm/set_union.hpp>
#include <testspr/sprout/algorithm/set_intersection.hpp>
#include <testspr/sprout/algorithm/set_difference.hpp>
#include <testspr/sprout/algorithm/set_symmetric_difference.hpp>
#include <testspr/sprout/algorithm/push_heap.hpp>
#include <testspr/sprout/algorithm/pop_heap.hpp>
#include <testspr/sprout/algorithm/make_heap.hpp>
#include <testspr/sprout/algorithm/make_partial_heap.hpp>
#include <testspr/sprout/algorithm/sort_heap.hpp>
#include <testspr/sprout/algorithm/swap_element.hpp>
#include <testspr/sprout/algorithm/swap_element_copy.hpp>
#include <testspr/sprout/algorithm/bogo_sort.hpp>
#include <testspr/sprout/algorithm/bogo_sort_result.hpp>

namespace testspr {
	static void algorithm_test() {
		testspr::algorithm_copy_test();
		testspr::algorithm_copy_n_test();
		testspr::algorithm_copy_if_test();
		testspr::algorithm_copy_backward_test();
		testspr::algorithm_transform_test();
		testspr::algorithm_replace_test();
		testspr::algorithm_replace_if_test();
		testspr::algorithm_replace_copy_test();
		testspr::algorithm_replace_copy_if_test();
		testspr::algorithm_fill_test();
		testspr::algorithm_fill_n_test();
		testspr::algorithm_generate_test();
		testspr::algorithm_generate_n_test();
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
		testspr::algorithm_swap_element_test();
		testspr::algorithm_swap_element_copy_test();
		testspr::algorithm_bogo_sort_test();
		testspr::algorithm_bogo_sort_result_test();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_HPP

