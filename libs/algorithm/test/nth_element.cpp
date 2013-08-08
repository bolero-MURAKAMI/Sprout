/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_NTH_ELEMENT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_NTH_ELEMENT_CPP

#include <sprout/algorithm/nth_element.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_nth_element_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					arr1,
					sprout::begin(arr1) + 4
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 10>{{2, 4, 1, 3, 5, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					arr1,
					sprout::begin(arr1) + 4
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 5>{{2, 4, 1, 3, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 6>{{2, 3, 5, 9, 8, 6}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 3>{{2, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// ソート
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					arr1,
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 10>{{2, 4, 1, 3, 5, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					arr1,
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 5>{{2, 4, 1, 3, 5}}
					));
			}
			// ソート
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 6>{{2, 3, 5, 9, 8, 6}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					nth,
					array<int, 3>{{2, 3, 5}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_nth_element_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NTH_ELEMENT_CPP
