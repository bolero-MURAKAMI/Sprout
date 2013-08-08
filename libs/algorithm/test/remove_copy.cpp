/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_CPP

#include <sprout/algorithm/remove_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 2>{{}};

			// [2 .. 8) の範囲を削除 (0)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{3, 5, 7, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) の範囲を削除 (0)
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{3, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{3, 5}}
					));
			}
			// [2 .. 8) の範囲を削除 (0)
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{3, 5, 7, 0, 0, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_remove_copy_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_REMOVE_COPY_CPP
