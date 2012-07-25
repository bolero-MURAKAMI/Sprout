#ifndef SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_CPP

#include <sprout/algorithm/bozo_sort.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_bozo_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort(
					arr1,
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bozo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bozo_sort(
					sprout::sub(arr1, 1, 4),
					sprout::random::default_random_engine(SPROUT_UNIQUE_SEED),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sorted,
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(sorted),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_bozo_sort_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_BOZO_SORT_CPP
