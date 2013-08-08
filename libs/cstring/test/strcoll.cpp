/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRCOLL_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRCOLL_CPP

#include <sprout/cstring/strcoll.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strcoll_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str1[] = "ABC";
			SPROUT_STATIC_CONSTEXPR char str2[] = "ABD";
			SPROUT_STATIC_CONSTEXPR char str3[] = "B";
			SPROUT_STATIC_CONSTEXPR char str4[] = "AAAA";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcoll(str, str1);
				TESTSPR_BOTH_ASSERT(result == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcoll(str, str2);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcoll(str, str3);
				TESTSPR_BOTH_ASSERT(result < 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcoll(str, str4);
				TESTSPR_BOTH_ASSERT(result > 0);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strcoll_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRCOLL_CPP
