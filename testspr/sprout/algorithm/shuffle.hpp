#ifndef TESTSPR_SPROUT_ALGORITHM_SHUFFLE_HPP
#define TESTSPR_SPROUT_ALGORITHM_SHUFFLE_HPP

#include <sprout/algorithm/shuffle.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_shuffle_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// シャッフル
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::shuffle(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					shuffled,
					arr1
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::fit::shuffle(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					shuffled,
					arr1
					));
			}
			// シャッフル
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::shuffle(
					sprout::sub(arr1, 2, 8),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					shuffled,
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					sprout::get_internal(shuffled),
					arr1
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto shuffled = sprout::fit::shuffle(
					sprout::sub(arr1, 2, 8),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					shuffled,
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_DOUBLE_ASSERT(testspr::is_permutation(
					sprout::get_internal(shuffled),
					arr1
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_SHUFFLE_HPP

