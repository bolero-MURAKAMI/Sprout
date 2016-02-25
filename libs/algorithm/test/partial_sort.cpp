/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_PARTIAL_SORT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_PARTIAL_SORT_CPP

#include <sprout/algorithm/partial_sort.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_partial_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 9, 8, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{2, 3, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 9, 8, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::partial_sort(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{2, 3, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 9, 8, 7, 10, 6}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_partial_sort_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_PARTIAL_SORT_CPP
