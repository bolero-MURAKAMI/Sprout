/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_CSTRING_TEST_CSTRING_CPP
#define SPROUT_LIBS_CSTRING_TEST_CSTRING_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_CSTRING_TEST_CSTRING_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./memcmp.cpp"
#include "./strcmp.cpp"
#include "./strcoll.cpp"
#include "./strncmp.cpp"
#include "./memchr.cpp"
#include "./strchr.cpp"
#include "./strcspn.cpp"
#include "./strpbrk.cpp"
#include "./strrchr.cpp"
#include "./strspn.cpp"
#include "./strstr.cpp"
#include "./strlen.cpp"

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_CSTRING_TEST_CSTRING_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void cstring_test() {
		testspr::cstring_memcmp_test();
		testspr::cstring_strcmp_test();
		testspr::cstring_strcoll_test();
		testspr::cstring_strncmp_test();
		testspr::cstring_memchr_test();
		testspr::cstring_strchr_test();
		testspr::cstring_strcspn_test();
		testspr::cstring_strpbrk_test();
		testspr::cstring_strrchr_test();
		testspr::cstring_strspn_test();
		testspr::cstring_strstr_test();
		testspr::cstring_strlen_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::cstring_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_CSTRING_TEST_CSTRING_CPP
