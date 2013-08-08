/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_UNTIL_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_UNTIL_CPP

#include <sprout/algorithm/is_heap_until.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_is_heap_until_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 3, 4, 1}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{10, 9, 8, 6, 7, 2, 5, 13, 14, 11}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr2),
					sprout::begin(arr2) + 5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					sprout::begin(arr2),
					sprout::begin(arr2) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 5);
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2)),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 7);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::is_heap_until(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2) + 5),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr2) + 5);
			}
#endif
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_is_heap_until_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_HEAP_UNTIL_CPP
