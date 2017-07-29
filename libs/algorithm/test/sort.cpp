/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_SORT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SORT_CPP

#include <sprout/algorithm/sort.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::sort(
					sprout::sub(arr1, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::sort(
					sprout::sub(arr1, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_sort_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SORT_CPP
