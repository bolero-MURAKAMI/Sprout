/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_FILL_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_FILL_CPP

#include <sprout/algorithm/fill.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_fill_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// fill (-1)
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill(
					arr1,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill(
					arr1,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}
					));
			}
			// fill (-1)
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill(
					sprout::sub(arr1, 2, 8),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 6>{{-1, -1, -1, -1, -1, -1}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, -1, -1, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill(
					sprout::sub(arr1, 2, 8),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 6>{{-1, -1, -1, -1, -1, -1}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, -1, -1, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_fill_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_FILL_CPP
