#ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_CPP

#include <sprout/algorithm/is_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_is_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 13, 14, 11}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr2),
					sprout::begin(arr2) + 5
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					sprout::begin(arr2),
					sprout::begin(arr2) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_heap(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2) + 5),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
#endif
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_is_heap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_CPP
