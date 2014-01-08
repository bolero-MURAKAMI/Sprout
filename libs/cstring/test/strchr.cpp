/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRCHR_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRCHR_CPP

#include <sprout/cstring/strchr.hpp>
#include <sprout/iterator.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strchr_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "abcdefghijklmnabcdefghijklmn";
			SPROUT_STATIC_CONSTEXPR char c = 'd';

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strchr(str, c);
				TESTSPR_BOTH_ASSERT(sprout::distance(str, found) == 3);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strchr_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRCHR_CPP
