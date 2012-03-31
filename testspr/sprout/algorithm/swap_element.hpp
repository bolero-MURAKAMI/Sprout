#ifndef TESTSPR_SPROUT_ALGORITHM_SWAP_ELEMENT_HPP
#define TESTSPR_SPROUT_ALGORITHM_SWAP_ELEMENT_HPP

#include <sprout/algorithm/swap_element.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_swap_element_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// スワップ
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::swap_element(
					arr1,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					swapped,
					array<int, 10>{{1, 2, 8, 4, 5, 6, 7, 3, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::fit::swap_element(
					arr1,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					swapped,
					array<int, 10>{{1, 2, 8, 4, 5, 6, 7, 3, 9, 10}}
					));
			}
			// スワップ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::swap_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					swapped,
					array<int, 6>{{8, 4, 5, 6, 7, 3}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(swapped),
					array<int, 10>{{1, 2, 8, 4, 5, 6, 7, 3, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::fit::swap_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					swapped,
					array<int, 6>{{8, 4, 5, 6, 7, 3}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(swapped),
					array<int, 10>{{1, 2, 8, 4, 5, 6, 7, 3, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_SWAP_ELEMENT_HPP

