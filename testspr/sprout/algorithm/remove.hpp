#ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_HPP
#define TESTSPR_SPROUT_ALGORITHM_REMOVE_HPP

#include <sprout/algorithm/remove.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// çÌèú (0)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove(
					arr1,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{1, 3, 5, 7, 9, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove(
					arr1,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
			}
			// çÌèú (0)
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove(
					sprout::sub(arr1, 2, 8),
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{3, 5, 7, 0, 7, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{1, 0, 3, 5, 7, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove(
					sprout::sub(arr1, 2, 8),
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{1, 0, 3, 5, 7, 0, 7, 0, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_HPP

