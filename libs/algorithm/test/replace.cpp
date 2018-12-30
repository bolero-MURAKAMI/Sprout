/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REPLACE_CPP

#include <sprout/algorithm/replace.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// replace (0 -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace(
					arr1,
					0,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{1, -1, 3, -1, 5, -1, 7, -1, 9, -1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace(
					arr1,
					0,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{1, -1, 3, -1, 5, -1, 7, -1, 9, -1}}
					));
			}
			// replace (0 -> -1)
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace(
					sprout::sub(arr1, 2, 8),
					0,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, 3, -1, 5, -1, 7, -1, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace(
					sprout::sub(arr1, 2, 8),
					0,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, 3, -1, 5, -1, 7, -1, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_replace_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_CPP
