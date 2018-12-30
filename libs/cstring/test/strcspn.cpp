/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRCSPN_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRCSPN_CPP

#include <sprout/cstring/strcspn.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strcspn_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "abcdefgabcdefghij";
			SPROUT_STATIC_CONSTEXPR char str1[] = "hj";
			SPROUT_STATIC_CONSTEXPR char str2[] = "ghj";

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcspn(str, str1);
				TESTSPR_BOTH_ASSERT(result == 14);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::strcspn(str, str2);
				TESTSPR_BOTH_ASSERT(result == 6);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strcspn_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRCSPN_CPP
