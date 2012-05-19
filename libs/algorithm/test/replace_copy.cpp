#ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REPLACE_COPY_CPP

#include <sprout/algorithm/replace_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) の範囲を置換 (0 -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{3, -1, 5, -1, 7, -1, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
			}
			// [2 .. 8) の範囲を置換 (0 -> -1)
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 4>{{3, -1, 5, -1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 4>{{3, -1, 5, -1}}
					));
			}
			// [2 .. 8) の範囲を置換 (0 -> -1)
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{0, 0, 3, -1, 5, -1, 7, -1, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0,
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{3, -1, 5, -1, 7, -1}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(replaced),
					array<int, 10>{{0, 0, 3, -1, 5, -1, 7, -1, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_replace_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REPLACE_COPY_CPP

