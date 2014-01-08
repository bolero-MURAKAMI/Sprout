/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_PUSH_HEAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_PUSH_HEAP_CPP

#include <sprout/algorithm/push_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_push_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 9, 6, 4, 5, 3, 1, 2, 7}};

			// ヒープにプッシュ
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			// ヒープにプッシュ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 9, 6, 4, 5, 3, 1, 2, 7}};

			// ヒープにプッシュ
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					arr1,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}}
					));
			}
			// ヒープにプッシュ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::push_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::push_heap(
					sprout::sub(arr1, 2, 10),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{9, 7, 4, 6, 3, 1, 2, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 9, 7, 4, 6, 3, 1, 2, 5}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_push_heap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_PUSH_HEAP_CPP
