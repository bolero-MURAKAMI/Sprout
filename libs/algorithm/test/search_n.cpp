/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_SEARCH_N_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_SEARCH_N_CPP

#include <sprout/algorithm/search_n.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_search_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 5, 5, 5, 5, 8, 9, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::end(arr1),
					2,
					5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::end(arr1),
					4,
					5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					2,
					5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					4,
					5
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::end(arr1),
					2,
					5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::end(arr1),
					4,
					5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					2,
					5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					4,
					5,
					testspr::equal_to<int>()
					);
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					2,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					4,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					2,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					4,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					2,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1)),
					4,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					2,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5),
					4,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					2,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					4,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					2,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					4,
					5
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					2,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1)),
					4,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					2,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::search_n(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5),
					4,
					5,
					testspr::equal_to<int>()
					).base();
				TESTSPR_BOTH_ASSERT(found == sprout::begin(arr1) + 5);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_search_n_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_SEARCH_N_CPP
