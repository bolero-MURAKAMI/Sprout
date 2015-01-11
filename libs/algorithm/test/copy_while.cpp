/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_WHILE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_COPY_WHILE_CPP

#include <sprout/algorithm/copy_while.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_copy_while_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// copy less than 6
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr2,
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 10>{{1, 2, 3, 4, 5, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr2,
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// copy less than 8
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr3,
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{1, 2, 3, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr3,
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{1, 2, 3, 4}}
					));
			}
			// copy less than 8
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::sub(arr2, 2, 8),
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{1, 2, 3, 4, 5, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 5, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_while(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::sub(arr2, 2, 8),
					testspr::less_than<int>(6)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 5, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_copy_while_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_WHILE_CPP
