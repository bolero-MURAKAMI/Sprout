#ifndef SPROUT_LIBS_ALGORITHM_TEST_MAKE_HEAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MAKE_HEAP_CPP

#include <sprout/algorithm/make_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_make_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ヒープ作成
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_heap(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}}
					));
			}
			// ヒープ作成
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 6, 8, 2, 5, 3, 4, 1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 9, 6, 8, 2, 5, 3, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 6, 8, 2, 5, 3, 4, 1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 9, 6, 8, 2, 5, 3, 4, 1}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ヒープ作成
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}}
					));
			}
			// ヒープ作成
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 6, 8, 2, 5, 3, 4, 1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 9, 6, 8, 2, 5, 3, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 6, 8, 2, 5, 3, 4, 1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 9, 6, 8, 2, 5, 3, 4, 1}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_make_heap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MAKE_HEAP_CPP

