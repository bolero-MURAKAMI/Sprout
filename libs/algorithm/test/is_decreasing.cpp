#ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_DECREASING_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_IS_DECREASING_CPP

#include <sprout/algorithm/is_decreasing.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_is_decreasing_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 6, 4, 2, 9, 7, 5, 3, 1}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_decreasing(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_decreasing(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(result);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_is_decreasing_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_DECREASING_CPP
