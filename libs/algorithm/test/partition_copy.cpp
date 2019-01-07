/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_PARTITION_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_PARTITION_COPY_CPP

#include <sprout/algorithm/partition_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_partition_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// partition in range [2 .. 8) (odd)
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 10>{{7, 5, 3, 4, 6, 8, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{7, 5, 3}}
					));
			}
			// partition in range [2 .. 8) (odd)
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 4>{{5, 3, 4, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 2>{{5, 3}}
					));
			}
			// partition in range [2 .. 8) (odd)
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 6>{{7, 5, 3, 4, 6, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{0, 0, 7, 5, 3, 4, 6, 8, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{7, 5, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{0, 0, 7, 5, 3, 4, 6, 8, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_partition_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_PARTITION_COPY_CPP
