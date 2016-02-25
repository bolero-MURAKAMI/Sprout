/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_IF_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REPLACE_IF_CPP

#include <sprout/algorithm/replace_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// replace (odd -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_if(
					arr1,
					is_odd<int>(),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{-1, 0, -1, 0, -1, 0, -1, 0, -1, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_if(
					arr1,
					is_odd<int>(),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{-1, 0, -1, 0, -1, 0, -1, 0, -1, 0}}
					));
			}
			// replace (odd -> -1)
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_if(
					sprout::sub(arr1, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, -1, 0, -1, 0, -1, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_if(
					sprout::sub(arr1, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, -1, 0, -1, 0, -1, 0, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_replace_if_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_IF_CPP
