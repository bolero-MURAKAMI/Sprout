/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_CPP

#include <sprout/algorithm/random_swap.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_random_swap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ランダムスワップ
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::random_swap(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					random_swapped,
					arr1
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::fit::random_swap(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					random_swapped,
					arr1
					));
			}
			// ランダムスワップ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::random_swap(
					sprout::sub(arr1, 2, 8),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					random_swapped,
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(random_swapped),
					arr1
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::fit::random_swap(
					sprout::sub(arr1, 2, 8),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					random_swapped,
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(random_swapped),
					arr1
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_random_swap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_CPP
