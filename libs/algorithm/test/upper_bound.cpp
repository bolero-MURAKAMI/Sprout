/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_UPPER_BOUND_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_UPPER_BOUND_CPP

#include <sprout/algorithm/upper_bound.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_upper_bound_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 7, 7, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					sprout::begin(arr1),
					sprout::end(arr1),
					7
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					7,
					testspr::less<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					7
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					7,
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					7
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 9);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::upper_bound(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					7,
					testspr::less<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_upper_bound_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_UPPER_BOUND_CPP
