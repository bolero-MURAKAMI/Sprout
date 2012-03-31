#ifndef TESTSPR_SPROUT_ALGORITHM_FILL_HPP
#define TESTSPR_SPROUT_ALGORITHM_FILL_HPP

#include <sprout/algorithm/fill.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_fill_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// è[ìU (-1)
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill(
					arr1,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					filled,
					array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill(
					arr1,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					filled,
					array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}
					));
			}
			// è[ìU (-1)
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fill(
					sprout::sub(arr1, 2, 8),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					filled,
					array<int, 6>{{-1, -1, -1, -1, -1, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, -1, -1, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto filled = sprout::fit::fill(
					sprout::sub(arr1, 2, 8),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					filled,
					array<int, 6>{{-1, -1, -1, -1, -1, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(filled),
					array<int, 10>{{1, 2, -1, -1, -1, -1, -1, -1, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_FILL_HPP

