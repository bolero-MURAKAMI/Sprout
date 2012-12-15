#ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP

#include <sprout/algorithm/equal_range.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_equal_range_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 7, 7, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					sprout::begin(arr1),
					sprout::end(arr1),
					7
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 6);
				TESTSPR_BOTH_ASSERT(found.second == sprout::begin(arr1) + 9);
				TESTSPR_BOTH_ASSERT(found.second - found.first == 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(found.second == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(found.second - found.first == 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_equal_range_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP
