/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_RESULT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_RESULT_CPP

#include <sprout/algorithm/bozo_sort_result.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_bozo_sort_result_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::default_random_engine(SPROUT_UNIQUE_SEED);

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort_result(
					sprout::sub(arr1, 1, 4),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort_result(
					sprout::sub(arr1, 1, 4),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::default_random_engine(SPROUT_UNIQUE_SEED);

			// sort
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort_result(
					arr1,
					g,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort_result(
					arr1,
					g,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			// sort
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort_result(
					sprout::sub(arr1, 1, 4),
					g,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort_result(
					sprout::sub(arr1, 1, 4),
					g,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bozo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_bozo_sort_result_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_RESULT_CPP
