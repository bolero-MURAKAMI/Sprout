#ifndef SPROUT_LIBS_ALGORITHM_TEST_ROTATE_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_ROTATE_COPY_CPP

#include <sprout/algorithm/rotate_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_rotate_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) の範囲を回転
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 10>{{6, 7, 8, 3, 4, 5, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::fit::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 6>{{6, 7, 8, 3, 4, 5}}
					));
			}
			// [2 .. 8) の範囲を回転
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 4>{{6, 7, 8, 3}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::fit::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 4>{{6, 7, 8, 3}}
					));
			}
			// [2 .. 8) の範囲を回転
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 6>{{6, 7, 8, 3, 4, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(rotated),
					array<int, 10>{{0, 0, 6, 7, 8, 3, 4, 5, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::fit::rotate_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 5,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 6>{{6, 7, 8, 3, 4, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(rotated),
					array<int, 10>{{0, 0, 6, 7, 8, 3, 4, 5, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_rotate_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_ROTATE_COPY_CPP

