/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_GENERATE_N_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_GENERATE_N_CPP

#include <sprout/algorithm/generate_n.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_generate_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{}};

			// generate
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate_n(
					arr1,
					4,
					testspr::gen_iota<int>(1)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{1, 2, 3, 4, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate_n(
					arr1,
					4,
					testspr::gen_iota<int>(1)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					generated,
					array<int, 4>{{1, 2, 3, 4}}
					));
			}
			// generate
			// from sub range
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::gen_iota<int>(1)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{1, 2, 3, 4, 0, 0}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::gen_iota<int>(1)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					generated,
					array<int, 4>{{1, 2, 3, 4}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{0, 0, 1, 2, 3, 4, 0, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_generate_n_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_GENERATE_N_CPP
