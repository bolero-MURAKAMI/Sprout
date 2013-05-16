#ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_EQUAL_CPP

#include <sprout/algorithm/equal.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_equal_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 10, 9, 8}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3)
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
#endif

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::begin(arr2)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::begin(arr3) + 5
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::begin(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::begin(arr3) + 5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::reduct_input(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::reduct_input(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::reduct_input(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::reduct_input(sprout::begin(arr3) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::reduct_input(sprout::end(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::reduct_input(sprout::end(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::reduct_input(sprout::begin(arr3) + 5),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::reduct_random_access(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::reduct_random_access(sprout::begin(arr3) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::reduct_random_access(sprout::end(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::equal(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::reduct_random_access(sprout::begin(arr3) + 5),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(result);
			}
#endif
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_equal_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_CPP
