#ifndef SPROUT_LIBS_ALGORITHM_TEST_CLAMP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_CLAMP_CPP

#include <sprout/algorithm/clamp.hpp>
#include <sprout/array.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_clamp_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 2>{{4, 7}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::clamp(
					0,
					arr1[0],
					arr1[1]
					);
				TESTSPR_BOTH_ASSERT(result == arr1[0]);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::clamp(
					10,
					arr1[0],
					arr1[1]
					);
				TESTSPR_BOTH_ASSERT(result == arr1[1]);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::clamp(
					5,
					arr1[0],
					arr1[1]
					);
				TESTSPR_BOTH_ASSERT(result == 5);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_clamp_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_CLAMP_CPP
