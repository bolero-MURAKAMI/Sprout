#ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_N_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_COPY_N_CPP

#include <sprout/algorithm/copy_n.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_copy_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// 6 要素をコピー
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_n(
					sprout::begin(arr1) + 2,
					6,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 10>{{3, 4, 5, 6, 7, 8, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_n(
					sprout::begin(arr1) + 2,
					6,
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
			}

			// 6 要素をコピー
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_n(
					sprout::begin(arr1) + 2,
					6,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{3, 4, 5, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_n(
					sprout::begin(arr1) + 2,
					6,
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{3, 4, 5, 6}}
					));
			}
			// 6 要素をコピー
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_n(
					sprout::begin(arr1) + 2,
					6,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_n(
					sprout::begin(arr1) + 2,
					6,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_copy_n_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_N_CPP
