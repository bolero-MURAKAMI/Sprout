#ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_IF_HPP
#define TESTSPR_SPROUT_ALGORITHM_REPLACE_IF_HPP

#include <sprout/algorithm/replace_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// íuä∑ (is_odd -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_if(
					arr1,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{-1, 0, -1, 0, -1, 0, -1, 0, -1, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_if(
					arr1,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{-1, 0, -1, 0, -1, 0, -1, 0, -1, 0}}
					));
			}
			// íuä∑ (is_odd -> -1)
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_if(
					sprout::sub(arr1, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, -1, 0, -1, 0, -1, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_if(
					sprout::sub(arr1, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{1, 0, -1, 0, -1, 0, -1, 0, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_IF_HPP

