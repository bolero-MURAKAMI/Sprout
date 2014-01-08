/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_SHUFFLE_RESULT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SHUFFLE_RESULT_CPP

#include <sprout/algorithm/shuffle_result.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_shuffle_result_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::default_random_engine(SPROUT_UNIQUE_SEED);

			// シャッフル
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::shuffle_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(shuffled),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto shuffled2 = sprout::shuffle_result(
					sprout::get<0>(shuffled),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(shuffled) == sprout::get<1>(shuffled2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::fit::shuffle_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(shuffled),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto shuffled2 = sprout::shuffle_result(
					sprout::get<0>(shuffled),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(shuffled) == sprout::get<1>(shuffled2));
			}
			// シャッフル
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::shuffle_result(
					sprout::sub(arr1, 2, 8),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(shuffled),
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(sprout::get<0>(shuffled)),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto shuffled2 = sprout::shuffle_result(
					sprout::get<0>(shuffled),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(shuffled) == sprout::get<1>(shuffled2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::fit::shuffle_result(
					sprout::sub(arr1, 2, 8),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(shuffled),
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(sprout::get<0>(shuffled)),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto shuffled2 = sprout::shuffle_result(
					sprout::get<0>(shuffled),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(shuffled) == sprout::get<1>(shuffled2));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_shuffle_result_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SHUFFLE_RESULT_CPP
