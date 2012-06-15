#ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_IF_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_IF_CPP

#include <sprout/algorithm/remove_copy_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_copy_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 2>{};

			// [2 .. 8) の範囲を削除 (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{0, 0, 0}}
					));
			}
			// [2 .. 8) の範囲を削除 (is_odd)
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{0, 0}}
					));
			}
			// [2 .. 8) の範囲を削除 (is_odd)
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{0, 0, 0, 0, 0, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{0, 0, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_remove_copy_if_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_IF_CPP
