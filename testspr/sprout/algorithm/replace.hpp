#ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_HPP
#define TESTSPR_SPROUT_ALGORITHM_REPLACE_HPP

#include <sprout/algorithm/replace.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// íuä∑ (0 -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace(
					arr1,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{1, -1, 3, -1, 5, -1, 7, -1, 9, -1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace(
					arr1,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{1, -1, 3, -1, 5, -1, 7, -1, 9, -1}}
					));
			}
			// íuä∑ (0 -> -1)
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace(
					sprout::sub(arr1, 2, 8),
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, 3, -1, 5, -1, 7, -1, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace(
					sprout::sub(arr1, 2, 8),
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, 3, -1, 5, -1, 7, -1, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_HPP

