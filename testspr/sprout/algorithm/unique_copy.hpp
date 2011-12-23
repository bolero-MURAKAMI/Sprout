#ifndef TESTSPR_SPROUT_ALGORITHM_UNIQUE_COPY_HPP
#define TESTSPR_SPROUT_ALGORITHM_UNIQUE_COPY_HPP

#include <sprout/algorithm/unique_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_unique_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 1, 3, 3, 5, 5, 7, 7, 9, 9}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 2>{};

			// [2 .. 8) の範囲「……ユニーク」
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 10>{{3, 5, 7, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) の範囲「……ユニーク」
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 2>{{3, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 2>{{3, 5}}
					));
			}
			// [2 .. 8) の範囲「……ユニーク」
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 6>{{3, 5, 7, 0, 0, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(uniqued),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(uniqued),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 1, 3, 3, 5, 5, 7, 7, 9, 9}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 2>{};

			// [2 .. 8) の範囲「……ユニーク」
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 10>{{3, 5, 7, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) の範囲「……ユニーク」
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 2>{{3, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 2>{{3, 5}}
					));
			}
			// [2 .. 8) の範囲「……ユニーク」
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 6>{{3, 5, 7, 0, 0, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(uniqued),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(uniqued),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_UNIQUE_COPY_HPP

