/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRSTR_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRSTR_CPP

#include <sprout/cstring/strstr.hpp>
#include <sprout/iterator.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strstr_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "abcdefghijklmn";
			SPROUT_STATIC_CONSTEXPR char str1[] = "defgh";
			SPROUT_STATIC_CONSTEXPR char str2[] = "xyz";
			SPROUT_STATIC_CONSTEXPR char str3[] = "abcdefghijklmnopqr";
			SPROUT_STATIC_CONSTEXPR char str4[] = "";

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strstr(str, str1);
				TESTSPR_BOTH_ASSERT(sprout::distance(str, found) == 3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strstr(str, str2);
				TESTSPR_BOTH_ASSERT(!found);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strstr(str, str3);
				TESTSPR_BOTH_ASSERT(!found);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strstr(str, str4);
				TESTSPR_BOTH_ASSERT(sprout::distance(str, found) == 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strstr_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRSTR_CPP
