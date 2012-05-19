#ifndef SPROUT_LIBS_ALGORITHM_TEST_GENERATE_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_GENERATE_CPP

#include <sprout/algorithm/generate.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_generate_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ê∂ê¨
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			// ê∂ê¨
			// îÕàÕÇÃêÿÇËèoÇµ
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_generate_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_GENERATE_CPP

