#ifndef TESTSPR_SPROUT_ALGORITHM_MAKE_PARTIAL_HEAP_HPP
#define TESTSPR_SPROUT_ALGORITHM_MAKE_PARTIAL_HEAP_HPP

#include <sprout/algorithm/make_partial_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_make_partial_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ヒープ作成
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{5, 4, 1, 3, 2, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 5>{{5, 4, 1, 3, 2}}
					));
			}
			// ヒープ作成
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{3, 1, 2, 9, 8, 6, 5, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 3>{{3, 1, 2}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ヒープ作成
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{5, 4, 1, 3, 2, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 5>{{5, 4, 1, 3, 2}}
					));
			}
			// ヒープ作成
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{3, 1, 2, 9, 8, 6, 5, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 3>{{3, 1, 2}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_MAKE_PARTIAL_HEAP_HPP

