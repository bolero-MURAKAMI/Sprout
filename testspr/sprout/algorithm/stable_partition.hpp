#ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_HPP
#define TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_HPP

#include <sprout/algorithm/stable_partition.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_stable_partition_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// パーティション (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::stable_partition(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 10>{{1, 3, 5, 7, 9, 2, 4, 6, 8, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::stable_partition(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
			}
			// パーティション (is_odd)
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::stable_partition(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 6>{{3, 5, 7, 4, 6, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{1, 2, 3, 5, 7, 4, 6, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::stable_partition(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{1, 2, 3, 5, 7, 4, 6, 8, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_HPP

