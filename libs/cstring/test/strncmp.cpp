/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRNCMP_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRNCMP_CPP

#include <sprout/cstring/strncmp.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strncmp_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str1[] = "ABD";
			SPROUT_STATIC_CONSTEXPR char str2[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str3[] = "AAA";
			SPROUT_STATIC_CONSTEXPR char str4[] = "ABCD";
			SPROUT_STATIC_CONSTEXPR char str5[] = "AB";
			SPROUT_STATIC_CONSTEXPR char str6[] = "B";
			SPROUT_STATIC_CONSTEXPR char str7[] = "A";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str1, 2);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str2, 2);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str3, 2);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str4, 2);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str5, 2);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str6, 2);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strncmp(str, str7, 2);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strncmp_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRNCMP_CPP
