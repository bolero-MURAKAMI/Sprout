/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_VERSION_NUMBER_HPP
#define SPROUT_PREDEF_VERSION_NUMBER_HPP

#include <sprout/config.hpp>

//
// SPROUT_VERSION_NUMBER
//
#define SPROUT_VERSION_NUMBER(MAJOR, MINOR, PATCH) \
    ( (((MAJOR) % 100) * 10000000) + (((MINOR) % 100) * 100000) + ((PATCH) % 100000) )

//
// SPROUT_VERSION_NUMBER_MAX
// SPROUT_VERSION_NUMBER_MIN
// SPROUT_VERSION_NUMBER_ZERO
//
#define SPROUT_VERSION_NUMBER_MAX \
    SPROUT_VERSION_NUMBER(99, 99, 99999)
#define SPROUT_VERSION_NUMBER_MIN \
    SPROUT_VERSION_NUMBER(0, 0, 1)
#define SPROUT_VERSION_NUMBER_ZERO \
    SPROUT_VERSION_NUMBER(0, 0, 0)

//
// SPROUT_VERSION_NUMBER_AVAILABLE
// SPROUT_VERSION_NUMBER_NOT_AVAILABLE
//
#define SPROUT_VERSION_NUMBER_AVAILABLE \
    SPROUT_VERSION_NUMBER_MIN
#define SPROUT_VERSION_NUMBER_NOT_AVAILABLE \
    SPROUT_VERSION_NUMBER_ZERO

#endif	// #ifndef SPROUT_PREDEF_OS_BSD_BSDI_HPP
