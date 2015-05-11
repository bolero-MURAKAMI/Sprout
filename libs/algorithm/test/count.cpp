/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_COUNT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_COUNT_CPP

#include <sprout/algorithm/count.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_count_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					sprout::begin(arr1),
					sprout::end(arr1),
					5
					);
				TESTSPR_BOTH_ASSERT(result == 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					sprout::begin(arr1),
					sprout::end(arr1),
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					5
					);
				TESTSPR_BOTH_ASSERT(result == 2);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					5
					);
				TESTSPR_BOTH_ASSERT(result == 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					5
					);
				TESTSPR_BOTH_ASSERT(result == 2);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					5
					);
				TESTSPR_BOTH_ASSERT(result == 4);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					5
					);
				TESTSPR_BOTH_ASSERT(result == 2);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::count(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					11
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_count_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_COUNT_CPP
