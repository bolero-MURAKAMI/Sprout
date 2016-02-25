/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_SET_UNION_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SET_UNION_CPP

#include <sprout/algorithm/set_union.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_set_union_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 10, 15, 20, 25}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 5>{{10, 20, 30, 40, 50}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// union
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{5, 10, 15, 20, 25, 30, 40, 50, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 8>{{5, 10, 15, 20, 25, 30, 40, 50}}
					));
			}
			// union
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 10, 15, 20}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 10, 15, 20}}
					));
			}
			// union
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 10, 15, 20, 25, 30}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 5, 10, 15, 20, 25, 30, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 10, 15, 20, 25, 30}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 5, 10, 15, 20, 25, 30, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 10, 15, 20, 25}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 5>{{10, 20, 30, 40, 50}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// union
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{5, 10, 15, 20, 25, 30, 40, 50, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 8>{{5, 10, 15, 20, 25, 30, 40, 50}}
					));
			}
			// union
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 10, 15, 20}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 10, 15, 20}}
					));
			}
			// union
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 10, 15, 20, 25, 30}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 5, 10, 15, 20, 25, 30, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_union(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 10, 15, 20, 25, 30}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(merged),
					array<int, 10>{{0, 0, 5, 10, 15, 20, 25, 30, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_set_union_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SET_UNION_CPP
