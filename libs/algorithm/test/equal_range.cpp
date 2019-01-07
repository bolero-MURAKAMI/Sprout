/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP

#include <sprout/algorithm/equal_range.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <sprout/iterator.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_equal_range_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 7, 7, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					sprout::begin(arr1),
					sprout::end(arr1),
					7
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 6);
				TESTSPR_BOTH_ASSERT(found.second == sprout::begin(arr1) + 9);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first, found.second) == 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(found.second == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first, found.second) == 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::end(arr1)),
					7
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 6);
				TESTSPR_BOTH_ASSERT(found.second.base() == sprout::begin(arr1) + 9);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first.base(), found.second.base()) == 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					testspr::reduce_forward(sprout::begin(arr1)),
					testspr::reduce_forward(sprout::begin(arr1) + 5),
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(found.second.base() == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first.base(), found.second.base()) == 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					7
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 6);
				TESTSPR_BOTH_ASSERT(found.second.base() == sprout::begin(arr1) + 9);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first.base(), found.second.base()) == 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::equal_range(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found.first.base() == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(found.second.base() == sprout::begin(arr1) + 5);
				TESTSPR_BOTH_ASSERT(sprout::distance(found.first.base(), found.second.base()) == 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_equal_range_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_EQUAL_RANGE_CPP
