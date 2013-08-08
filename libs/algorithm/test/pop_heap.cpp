/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_POP_HEAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_POP_HEAP_CPP

#include <sprout/algorithm/pop_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_pop_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 8, 9, 6, 7, 5, 3, 1, 2, 4}};

			// ヒープからポップ
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::pop_heap(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{9, 8, 5, 6, 7, 4, 3, 1, 2, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::pop_heap(
					arr1
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 9>{{9, 8, 5, 6, 7, 4, 3, 1, 2}}
					));
			}
			// ヒープからポップ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::pop_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{7, 6, 4, 5, 3, 1, 2, 9}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 7, 6, 4, 5, 3, 1, 2, 9}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::pop_heap(
					sprout::sub(arr1, 2, 10)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 7>{{7, 6, 4, 5, 3, 1, 2}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 8, 7, 6, 4, 5, 3, 1, 2, 9}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_pop_heap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_POP_HEAP_CPP
