/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_RECURRENCE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_RECURRENCE_CPP

#include <sprout/algorithm/recurrence.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_recurrence_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// generate
			{
				SPROUT_STATIC_CONSTEXPR auto recurrenced = sprout::recurrence(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					recurrenced,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto recurrenced = sprout::fit::recurrence(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					recurrenced,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			// generate
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto recurrenced = sprout::recurrence(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					recurrenced,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(recurrenced),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto recurrenced = sprout::fit::recurrence(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					recurrenced,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(recurrenced),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_recurrence_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_RECURRENCE_CPP
