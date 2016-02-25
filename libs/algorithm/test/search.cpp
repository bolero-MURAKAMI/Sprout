/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_SEARCH_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SEARCH_CPP

#include <sprout/algorithm/search.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_search_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 3>{{4, 5, 6}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 3>{{6, 5, 4}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::end(arr3)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::end(arr3),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					testspr::reduce_forward(sprout::begin(arr2)),
					testspr::reduce_forward(sprout::end(arr2))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					testspr::reduce_forward(sprout::begin(arr3)),
					testspr::reduce_forward(sprout::end(arr3))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					testspr::reduce_forward(sprout::begin(arr2)),
					testspr::reduce_forward(sprout::end(arr2))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					testspr::reduce_forward(sprout::begin(arr3)),
					testspr::reduce_forward(sprout::end(arr3))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					testspr::reduce_forward(sprout::begin(arr2)),
					testspr::reduce_forward(sprout::end(arr2)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					testspr::reduce_forward(sprout::begin(arr3)),
					testspr::reduce_forward(sprout::end(arr3)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					testspr::reduce_forward(sprout::begin(arr2)),
					testspr::reduce_forward(sprout::end(arr2)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					testspr::reduce_forward(sprout::begin(arr3)),
					testspr::reduce_forward(sprout::end(arr3)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::end(arr1));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_search_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SEARCH_CPP
