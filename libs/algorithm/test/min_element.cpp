/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_MIN_ELEMENT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_MIN_ELEMENT_CPP

#include <sprout/algorithm/min_element.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_min_element_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{6, 5, 7, 4, 8, 3, 9, 2, 10, 1}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1))
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}

#if defined(__clang__)
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1))
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5)
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::min_element(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(result == sprout::begin(arr1) + 3);
			}
#endif
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_min_element_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_MIN_ELEMENT_CPP
