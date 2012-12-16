#ifndef SPROUT_LIBS_ALGORITHM_TEST_MAX_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MAX_CPP

#include <sprout/algorithm/max.hpp>
#include <sprout/array.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_max_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 2>{{-1, 1}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::max(
					arr1[0],
					arr1[1]
					);
				TESTSPR_BOTH_ASSERT(result == arr1[1]);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::max(
					arr1[1],
					arr1[0]
					);
				TESTSPR_BOTH_ASSERT(result == arr1[1]);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::max(
					arr1[0],
					arr1[1],
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == arr1[1]);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::max(
					arr1[1],
					arr1[0],
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == arr1[1]);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_max_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MAX_CPP
