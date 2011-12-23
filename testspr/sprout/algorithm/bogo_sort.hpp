#ifndef TESTSPR_SPROUT_ALGORITHM_BOGO_SORT_HPP
#define TESTSPR_SPROUT_ALGORITHM_BOGO_SORT_HPP

#include <sprout/algorithm/sort.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_bogo_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort(
					arr1,
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_BOGO_SORT_HPP

