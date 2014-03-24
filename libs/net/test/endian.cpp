/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Copyright (c) 2014 Chris KAY
  https://github.com/cjkay-cpp-utils/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_NET_TEST_ENDIAN_CPP
#define SPROUT_LIBS_NET_TEST_ENDIAN_CPP

#include <sprout/net/endian.hpp>
#include <testspr/tools.hpp>
#include <iostream>

namespace testspr {
    static void endian_test() {
        using namespace sprout;

        {
            TESTSPR_ASSERT(sprout::net::detail::reverse(0xDEADBEEF) == 0xEFBEADDE);
            TESTSPR_ASSERT(sprout::net::detail::reverse(0xEFBEADDE) == 0xDEADBEEF);

            TESTSPR_ASSERT(sprout::net::detail::reverse_words(0xDEADBEEF) == 0xADDEEFBE);
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(0xADDEEFBE) == 0xDEADBEEF);
        }
    }
}   // namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::endian_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_NET_TEST_ENDIAN_CPP