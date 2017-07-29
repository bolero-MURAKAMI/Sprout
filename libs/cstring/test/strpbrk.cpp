/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_STRPBRK_CPP
#define SPROUT_LIBS_CSTRING_TEST_STRPBRK_CPP

#include <sprout/cstring/strpbrk.hpp>
#include <sprout/iterator.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void cstring_strpbrk_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char str[] = "abcdefgabcdefghij";
			SPROUT_STATIC_CONSTEXPR char str1[] = "ghsp";
			SPROUT_STATIC_CONSTEXPR char str2[] = "sp";

			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strpbrk(str, str1);
				TESTSPR_BOTH_ASSERT(sprout::distance(str, found) == 6);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto found = sprout::strpbrk(str, str2);
				TESTSPR_BOTH_ASSERT(!found);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_strpbrk_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_STRPBRK_CPP
