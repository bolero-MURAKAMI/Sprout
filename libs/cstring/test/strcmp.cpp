/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRCMP_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRCMP_CPP

#include <sprout/cstring/strcmp.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strcmp_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str1[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str2[] = "ABD";
			SPROUT_STATIC_CONSTEXPR char str3[] = "B";
			SPROUT_STATIC_CONSTEXPR char str4[] = "AAAA";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcmp(str, str1);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcmp(str, str2);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcmp(str, str3);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcmp(str, str4);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strcmp_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRCMP_CPP
