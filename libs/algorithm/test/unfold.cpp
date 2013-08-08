/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_CPP

#include <sprout/algorithm/unfold.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_unfold_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{}};

			// ê∂ê¨
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::unfold(
					arr1,
					testspr::unf_iota<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::fit::unfold(
					arr1,
					testspr::unf_iota<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// ê∂ê¨
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::unfold(
					sprout::sub(arr1, 2, 8),
					testspr::unf_iota<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 6>{{1, 2, 3, 4, 5, 6}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(unfolded),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 5, 6, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::fit::unfold(
					sprout::sub(arr1, 2, 8),
					testspr::unf_iota<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 6>{{1, 2, 3, 4, 5, 6}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(unfolded),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 5, 6, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_unfold_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_CPP
