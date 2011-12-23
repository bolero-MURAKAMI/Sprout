#ifndef TESTSPR_SPROUT_ALGORITHM_PARTITION_HPP
#define TESTSPR_SPROUT_ALGORITHM_PARTITION_HPP

#include <sprout/algorithm/partition.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_partition_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// パーティション (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::partition(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 10>{{9, 7, 5, 3, 1, 2, 4, 6, 8, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::partition(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 5>{{9, 7, 5, 3, 1}}
					));
			}
			// パーティション (is_odd)
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::partition(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 6>{{7, 5, 3, 4, 6, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(partitioned),
					array<int, 10>{{1, 2, 7, 5, 3, 4, 6, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::partition(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{7, 5, 3}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(partitioned),
					array<int, 10>{{1, 2, 7, 5, 3, 4, 6, 8, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_PARTITION_HPP

