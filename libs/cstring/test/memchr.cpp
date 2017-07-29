/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP
#define SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP

#include <sprout/cstring/memchr.hpp>
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
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_memchr_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_MEMCHR_CPP
