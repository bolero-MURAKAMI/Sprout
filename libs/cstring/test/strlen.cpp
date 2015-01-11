/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRLEN_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRLEN_CPP

#include <sprout/cstring/strlen.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strlen_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str1[] = "today";
			SPROUT_STATIC_CONSTEXPR char str2[] = "hello world";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strlen(str1);
				TESTSPR_BOTH_ASSERT(result == 5);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strlen(str2);
				TESTSPR_BOTH_ASSERT(result == 11);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strlen_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRLEN_CPP
