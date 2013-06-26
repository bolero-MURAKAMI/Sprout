#ifndef SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP
#define SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP

#include <sprout/cstring/memchr.hpp>
#include <sprout/iterator.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_memchr_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR unsigned char buf[] = "abcdef\0ghij";
			SPROUT_STATIC_CONSTEXPR unsigned char b = 'h';

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::memchr(buf, b, 12);
				TESTSPR_BOTH_ASSERT(buf + 8 == found);
//				TESTSPR_BOTH_ASSERT(sprout::distance(buf, reinterpret_cast<unsigned char const*>(found)) == 8);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_memchr_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP
