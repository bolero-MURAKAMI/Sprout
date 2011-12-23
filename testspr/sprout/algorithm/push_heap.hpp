#ifndef TESTSPR_SPROUT_ALGORITHM_PUSH_HEAP_HPP
#define TESTSPR_SPROUT_ALGORITHM_PUSH_HEAP_HPP

#include <sprout/algorithm/push_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_push_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 9, 6, 4, 5, 3, 1, 2, 7}};

			// ヒープにプッシュ
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			// ヒープにプッシュ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 9, 6, 4, 5, 3, 1, 2, 7}};

			// ヒープにプッシュ
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			// ヒープにプッシュ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_PUSH_HEAP_HPP

