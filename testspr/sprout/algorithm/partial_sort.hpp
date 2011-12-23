#ifndef TESTSPR_SPROUT_ALGORITHM_PARTIAL_SORT_HPP
#define TESTSPR_SPROUT_ALGORITHM_PARTIAL_SORT_HPP

#include <sprout/algorithm/partial_sort.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_partial_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 9, 8, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{2, 3, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 9, 8, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{2, 3, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_PARTIAL_SORT_HPP

