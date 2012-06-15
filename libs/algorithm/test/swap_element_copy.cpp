#ifndef SPROUT_LIBS_ALGORITHM_TEST_SWAP_ELEMENT_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SWAP_ELEMENT_COPY_CPP

#include <sprout/algorithm/swap_element_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_swap_element_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) の範囲をスワップ
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 10>{{8, 4, 5, 6, 7, 3, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::fit::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 6>{{8, 4, 5, 6, 7, 3}}
					));
			}
			// [2 .. 8) の範囲をスワップ
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 4>{{8, 4, 5, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::fit::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 4>{{8, 4, 5, 6}}
					));
			}
			// [2 .. 8) の範囲をスワップ
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 6>{{8, 4, 5, 6, 7, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(swapped),
					array<int, 10>{{0, 0, 8, 4, 5, 6, 7, 3, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto swapped = sprout::fit::swap_element_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 7
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					swapped,
					array<int, 6>{{8, 4, 5, 6, 7, 3}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(swapped),
					array<int, 10>{{0, 0, 8, 4, 5, 6, 7, 3, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_swap_element_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SWAP_ELEMENT_COPY_CPP
