/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_TRISTATE_LEXICOGRAPHICAL_COMPARE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_TRISTATE_LEXICOGRAPHICAL_COMPARE_CPP

#include <sprout/algorithm/tristate_lexicographical_compare.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_tristate_lexicographical_compare_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 1, 2, 3}};
			SPROUT_STATIC_CONSTEXPR auto arr4 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 11, 12, 13}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3)
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr4),
					sprout::end(arr4)
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::end(arr3)
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr4),
					sprout::end(arr4)
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::begin(arr2) + 5
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr3),
					sprout::end(arr3),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr4),
					sprout::end(arr4),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr2),
					sprout::end(arr2),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr3),
					sprout::end(arr3),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					sprout::begin(arr4),
					sprout::end(arr4),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr2),
					sprout::begin(arr2) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr3)),
					testspr::reduce_input(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr4)),
					testspr::reduce_input(sprout::end(arr4))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr3)),
					testspr::reduce_input(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr4)),
					testspr::reduce_input(sprout::end(arr4))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::begin(arr2) + 5)
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::end(arr2)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr3)),
					testspr::reduce_input(sprout::end(arr3)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr4)),
					testspr::reduce_input(sprout::end(arr4)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::end(arr2)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr3)),
					testspr::reduce_input(sprout::end(arr3)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::begin(arr1) + 5),
					testspr::reduce_input(sprout::begin(arr4)),
					testspr::reduce_input(sprout::end(arr4)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_input(sprout::begin(arr1)),
					testspr::reduce_input(sprout::end(arr1)),
					testspr::reduce_input(sprout::begin(arr2)),
					testspr::reduce_input(sprout::begin(arr2) + 5),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr4)),
					testspr::reduce_random_access(sprout::end(arr4))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr4)),
					testspr::reduce_random_access(sprout::end(arr4))
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::begin(arr2) + 5)
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr4)),
					testspr::reduce_random_access(sprout::end(arr4)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::end(arr2)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr3)),
					testspr::reduce_random_access(sprout::end(arr3)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::begin(arr1) + 5),
					testspr::reduce_random_access(sprout::begin(arr4)),
					testspr::reduce_random_access(sprout::end(arr4)),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::tristate_lexicographical_compare(
					testspr::reduce_random_access(sprout::begin(arr1)),
					testspr::reduce_random_access(sprout::end(arr1)),
					testspr::reduce_random_access(sprout::begin(arr2)),
					testspr::reduce_random_access(sprout::begin(arr2) + 5),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_tristate_lexicographical_compare_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_TRISTATE_LEXICOGRAPHICAL_COMPARE_CPP
