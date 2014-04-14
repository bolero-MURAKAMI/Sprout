/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_NEXT_PERMUTATION_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_NEXT_PERMUTATION_CPP

#include <sprout/algorithm/next_permutation.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_next_permutation_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{1, 2, 3, 4, 5}};

			// èáóÒ
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::next_permutation(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 5>{{1, 2, 3, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::fit::next_permutation(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 5>{{1, 2, 3, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			// èáóÒ
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::next_permutation(
					sprout::sub(arr1, 1, 4)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 3>{{2, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(permutation.first),
					array<int, 5>{{1, 2, 4, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::fit::next_permutation(
					sprout::sub(arr1, 1, 4)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 3>{{2, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(permutation.first),
					array<int, 5>{{1, 2, 4, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{1, 2, 3, 4, 5}};

			// èáóÒ
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::next_permutation(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 5>{{1, 2, 3, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::fit::next_permutation(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 5>{{1, 2, 3, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			// èáóÒ
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::next_permutation(
					sprout::sub(arr1, 1, 4),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 3>{{2, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(permutation.first),
					array<int, 5>{{1, 2, 4, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto permutation = sprout::fit::next_permutation(
					sprout::sub(arr1, 1, 4),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					permutation.first,
					array<int, 3>{{2, 4, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(permutation.first),
					array<int, 5>{{1, 2, 4, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(permutation.second);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_next_permutation_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NEXT_PERMUTATION_CPP
