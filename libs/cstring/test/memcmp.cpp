#ifndef SPROUT_LIBS_CSTRING_TEST_MEMCMP_CPP
#define SPROUT_LIBS_CSTRING_TEST_MEMCMP_CPP

#include <sprout/cstring/memcmp.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_memcmp_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR unsigned char buf[] = "\0abc\0de";
			SPROUT_STATIC_CONSTEXPR unsigned char buf2[] = "\0abc\0de";
			SPROUT_STATIC_CONSTEXPR unsigned char buf3[] = "\0abcdef";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::memcmp(buf, buf2, 7);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::memcmp(buf, buf3, 7);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_memcmp_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_MEMCMP_CPP
