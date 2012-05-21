#ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_IF_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REMOVE_IF_CPP

#include <sprout/algorithm/remove_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// çÌèú (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_if(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{0, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_if(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 5>{{0, 0, 0, 0, 0}}
					));
			}
			// çÌèú (is_odd)
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_if(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{0, 0, 0, 0, 7, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{1, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_if(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{0, 0, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{1, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_remove_if_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_IF_CPP
