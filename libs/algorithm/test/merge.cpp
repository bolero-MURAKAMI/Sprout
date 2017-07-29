/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_MERGE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MERGE_CPP

#include <sprout/algorithm/merge.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_merge_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 4>{{3, 5, 7, 9}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 4>{{2, 4, 6, 8}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// merge
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{2, 3, 4, 5, 6, 7, 8, 9, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 8>{{2, 3, 4, 5, 6, 7, 8, 9}}
					));
			}
			// merge
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{2, 3, 4, 5}}
					));
			}
			// merge
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 3, 4, 5, 6, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 2, 3, 4, 5, 6, 7, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 3, 4, 5, 6, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 2, 3, 4, 5, 6, 7, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 4>{{3, 5, 7, 9}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 4>{{2, 4, 6, 8}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// merge
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{2, 3, 4, 5, 6, 7, 8, 9, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 8>{{2, 3, 4, 5, 6, 7, 8, 9}}
					));
			}
			// merge
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{2, 3, 4, 5}}
					));
			}
			// merge
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 3, 4, 5, 6, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 2, 3, 4, 5, 6, 7, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::merge(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 3, 4, 5, 6, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 2, 3, 4, 5, 6, 7, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_merge_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MERGE_CPP
