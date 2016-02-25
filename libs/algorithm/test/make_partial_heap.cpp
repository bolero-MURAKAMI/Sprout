/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_MAKE_PARTIAL_HEAP_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MAKE_PARTIAL_HEAP_CPP

#include <sprout/algorithm/make_partial_heap.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_make_partial_heap_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// make heap
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{5, 4, 1, 3, 2, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 5>{{5, 4, 1, 3, 2}}
					));
			}
			// make heap
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{3, 1, 2, 9, 8, 6, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 3>{{3, 1, 2}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// make heap
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 10>{{5, 4, 1, 3, 2, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 5>{{5, 4, 1, 3, 2}}
					));
			}
			// make heap
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 8>{{3, 1, 2, 9, 8, 6, 5, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto heap = sprout::fit::make_partial_heap(
					sprout::sub(arr1, 2, 10),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					heap,
					array<int, 3>{{3, 1, 2}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(heap),
					array<int, 10>{{10, 7, 3, 1, 2, 9, 8, 6, 5, 4}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_make_partial_heap_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MAKE_PARTIAL_HEAP_CPP
