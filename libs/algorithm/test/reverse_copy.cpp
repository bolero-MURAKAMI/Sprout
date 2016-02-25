/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_REBERSE_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REBERSE_COPY_CPP

#include <sprout/algorithm/reverse_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_reverse_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{{}};

			// reverse in range [2 .. 8)
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 10>{{8, 7, 6, 5, 4, 3, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
			}
			// reverse in range [2 .. 8)
			// overrun from output range
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 4>{{8, 7, 6, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 4>{{8, 7, 6, 5}}
					));
			}
			// reverse in range [2 .. 8)
			// to sub range
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{0, 0, 8, 7, 6, 5, 4, 3, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{0, 0, 8, 7, 6, 5, 4, 3, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_reverse_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REBERSE_COPY_CPP
