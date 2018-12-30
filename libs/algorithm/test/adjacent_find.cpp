/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_ADJACENT_FIND_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_ADJACENT_FIND_CPP

#include <sprout/algorithm/adjacent_find.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_adjacent_find_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 12>{{1, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1))
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::adjacent_find(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_adjacent_find_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_ADJACENT_FIND_CPP
