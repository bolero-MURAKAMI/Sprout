#ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_PERTITIONED_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_IS_PERTITIONED_CPP

#include <sprout/algorithm/is_partitioned.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_is_partitioned_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 3, 5, 7, 9, 2, 4, 6, 8, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_partitioned(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_partitioned(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_partitioned(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_partitioned(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_is_partitioned_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_PERTITIONED_CPP
