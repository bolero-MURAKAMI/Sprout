/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_REBERSE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REBERSE_CPP

#include <sprout/algorithm/reverse.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_reverse_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// reverse
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}}
					));
			}
			// reverse
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{1, 2, 8, 7, 6, 5, 4, 3, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{1, 2, 8, 7, 6, 5, 4, 3, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_reverse_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REBERSE_CPP
