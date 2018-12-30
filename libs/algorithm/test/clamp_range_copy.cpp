/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_CLAMP_RANGE_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_CLAMP_RANGE_COPY_CPP

#include <sprout/algorithm/clamp_range_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_clamp_range_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// clamp in range [2 .. 8) (4 <= x <= 7)
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 10>{{4, 4, 5, 6, 7, 7, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
			}
			// clamp in range [2 .. 8) (4 <= x <= 7)
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 4>{{4, 4, 5, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 4>{{4, 4, 5, 6}}
					));
			}
			// clamp in range [2 .. 8) (4 <= x <= 7)
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(clamped),
					array<int, 10>{{0, 0, 4, 4, 5, 6, 7, 7, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					4,
					7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(clamped),
					array<int, 10>{{0, 0, 4, 4, 5, 6, 7, 7, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// clamp in range [2 .. 8) (4 <= x <= 7)
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 10>{{4, 4, 5, 6, 7, 7, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
			}
			// clamp in range [2 .. 8) (4 <= x <= 7)
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 4>{{4, 4, 5, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 4>{{4, 4, 5, 6}}
					));
			}
			// clamp in range [2 .. 8) (4 <= x <= 7)
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(clamped),
					array<int, 10>{{0, 0, 4, 4, 5, 6, 7, 7, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto clamped = sprout::fit::clamp_range_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					4,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					clamped,
					array<int, 6>{{4, 4, 5, 6, 7, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(clamped),
					array<int, 10>{{0, 0, 4, 4, 5, 6, 7, 7, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_clamp_range_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_CLAMP_RANGE_COPY_CPP
