#ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_IF_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_COPY_IF_CPP

#include <sprout/algorithm/copy_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_copy_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// 奇数をコピー
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr2,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 10>{{1, 3, 5, 7, 9, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr2,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
			}
			// 奇数をコピー
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr3,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{1, 3, 5, 7}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					arr3,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{1, 3, 5, 7}}
					));
			}
			// 奇数をコピー
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::sub(arr2, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{1, 3, 5, 7, 9, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 1, 3, 5, 7, 9, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_if(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::sub(arr2, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 1, 3, 5, 7, 9, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_copy_if_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_IF_CPP

