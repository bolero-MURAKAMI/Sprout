#ifndef SPROUT_LIBS_ALGORITHM_TEST_MISMATCH_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MISMATCH_CPP

#include <sprout/algorithm/mismatch.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_mismatch_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 10, 9, 8}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 10>{{10, 9, 8, 1, 2, 3, 4, 5, 6, 7}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2)
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3)
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2)
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3)
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1));
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1));
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::end(arr1)),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_input(sprout::begin(arr1)),
					testspr::reduct_input(sprout::begin(arr1) + 5),
					testspr::reduct_input(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3))
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::mismatch(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::reduct_random_access(sprout::begin(arr3)),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1));
			}
#endif
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_mismatch_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MISMATCH_CPP
