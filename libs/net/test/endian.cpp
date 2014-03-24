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

        { // 16
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint16_t(0x0A1B)) == uint16_t(0x1B0A));
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint16_t(0x1B0A)) == uint16_t(0x0A1B));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint16_t(0x0A1B)) == uint16_t(0x1B0A));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint16_t(0x1B0A)) == uint16_t(0x0A1B));
        }

        { // 32
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint32_t(0x0A1B2C3D)) == uint32_t(0x3D2C1B0A));
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint32_t(0x3D2C1B0A)) == uint32_t(0x0A1B2C3D));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint32_t(0x0A1B2C3D)) == uint32_t(0x1B0A3D2C));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint32_t(0x1B0A3D2C)) == uint32_t(0x0A1B2C3D));
        }

        { // 64
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint64_t(0x0A1B2C3D4E5F6A7B)) == uint64_t(0x7B6A5F4E3D2C1B0A));
            TESTSPR_ASSERT(sprout::net::detail::reverse(uint64_t(0x7B6A5F4E3D2C1B0A)) == uint64_t(0x0A1B2C3D4E5F6A7B));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint64_t(0x0A1B2C3D4E5F6A7B)) == uint64_t(0x1B0A3D2C5F4E7B6A));
            TESTSPR_ASSERT(sprout::net::detail::reverse_words(uint64_t(0x1B0A3D2C5F4E7B6A)) == uint64_t(0x0A1B2C3D4E5F6A7B));
        }
    }
}   // namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::endian_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_NET_TEST_ENDIAN_CPP