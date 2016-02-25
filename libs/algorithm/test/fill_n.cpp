/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_FILL_N_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_FILL_N_CPP

#include <sprout/algorithm/fill_n.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_fill_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// fill (-1)
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill_n(
					arr1,
					4,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 10>{{-1, -1, -1, -1, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill_n(
					arr1,
					4,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 4>{{-1, -1, -1, -1}}
					));
			}
			// fill (-1)
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill_n(
					sprout::sub(arr1, 2, 8),
					4,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 6>{{-1, -1, -1, -1, 7, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill_n(
					sprout::sub(arr1, 2, 8),
					4,
					-1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					filled,
					array<int, 4>{{-1, -1, -1, -1}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, 7, 8, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_fill_n_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_FILL_N_CPP
