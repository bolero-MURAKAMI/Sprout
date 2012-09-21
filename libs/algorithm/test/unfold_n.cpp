#ifndef SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_N_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_N_CPP

#include <sprout/algorithm/unfold_n.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_unfold_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ê∂ê¨
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::unfold_n(
					arr1,
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 10>{{1, 2, 4, 8, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::fit::unfold_n(
					arr1,
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 4>{{1, 2, 4, 8}}
					));
			}
			// ê∂ê¨
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::unfold_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 6>{{1, 2, 4, 8, 7, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(unfolded),
					array<int, 10>{{1, 2, 1, 2, 4, 8, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto unfolded = sprout::fit::unfold_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					unfolded,
					array<int, 4>{{1, 2, 4, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(unfolded),
					array<int, 10>{{1, 2, 1, 2, 4, 8, 7, 8, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_unfold_n_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_UNFOLD_N_CPP
