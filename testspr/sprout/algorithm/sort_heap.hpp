#ifndef TESTSPR_SPROUT_ALGORITHM_SORT_HEAP_HPP
#define TESTSPR_SPROUT_ALGORITHM_SORT_HEAP_HPP

#include <sprout/algorithm/sort_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_sort_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort_heap(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{10, 9, 2, 3, 5, 6, 7, 8, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort_heap(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{10, 9, 2, 3, 5, 6, 7, 8, 4, 1}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort_heap(
					sprout::sub(arr1, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{10, 9, 2, 3, 5, 6, 7, 8, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort_heap(
					sprout::sub(arr1, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{10, 9, 2, 3, 5, 6, 7, 8, 4, 1}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_SORT_HEAP_HPP

