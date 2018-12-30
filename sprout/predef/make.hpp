/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_MAKE_HPP
#define SPROUT_PREDEF_MAKE_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_PREDEF_MAKE_0X_VRP(V) SPROUT_VERSION_NUMBER((V & 0xF00) >> 8, (V & 0xF0) >> 4, (V & 0xF))
#define SPROUT_PREDEF_MAKE_0X_VVRP(V) SPROUT_VERSION_NUMBER((V & 0xFF00) >> 8, (V & 0xF0) >> 4, (V & 0xF))
#define SPROUT_PREDEF_MAKE_0X_VRPP(V) SPROUT_VERSION_NUMBER((V & 0xF000) >> 12, (V & 0xF00) >> 8, (V & 0xFF))
#define SPROUT_PREDEF_MAKE_0X_VVRR(V) SPROUT_VERSION_NUMBER((V & 0xFF00) >> 8, (V & 0xFF), 0)
#define SPROUT_PREDEF_MAKE_0X_VRRPPPP(V) SPROUT_VERSION_NUMBER((V & 0xF000000) >> 24, (V & 0xFF0000) >> 16, (V & 0xFFFF))
#define SPROUT_PREDEF_MAKE_0X_VVRRP(V) SPROUT_VERSION_NUMBER((V & 0xFF000) >> 12, (V & 0xFF0) >> 4, (V & 0xF))
#define SPROUT_PREDEF_MAKE_0X_VRRPP000(V) SPROUT_VERSION_NUMBER((V & 0xF0000000) >> 28, (V & 0xFF00000) >> 20, (V & 0xFF000) >> 12)
#define SPROUT_PREDEF_MAKE_0X_VVRRPP(V) SPROUT_VERSION_NUMBER((V & 0xFF0000) >> 16, (V & 0xFF00) >> 8, (V & 0xFF))
#define SPROUT_PREDEF_MAKE_10_VPPP(V) SPROUT_VERSION_NUMBER(((V) / 1000) % 10, 0, (V) % 1000)
#define SPROUT_PREDEF_MAKE_10_VRP(V) SPROUT_VERSION_NUMBER(((V) / 100) % 10, ((V) / 10) % 10, (V) % 10)
#define SPROUT_PREDEF_MAKE_10_VRP000(V) SPROUT_VERSION_NUMBER(((V) / 100000) % 10, ((V) / 10000) % 10, ((V) / 1000) % 10)
#define SPROUT_PREDEF_MAKE_10_VRPP(V) SPROUT_VERSION_NUMBER(((V) / 1000) % 10, ((V) / 100) % 10, (V) % 100)
#define SPROUT_PREDEF_MAKE_10_VRR(V) SPROUT_VERSION_NUMBER(((V) / 100) % 10, (V) % 100, 0)
#define SPROUT_PREDEF_MAKE_10_VRRPP(V) SPROUT_VERSION_NUMBER(((V) / 10000) % 10, ((V) / 100) % 100, (V) % 100)
#define SPROUT_PREDEF_MAKE_10_VRR000(V) SPROUT_VERSION_NUMBER(((V) / 100000) % 10, ((V) / 1000) % 100, 0)
#define SPROUT_PREDEF_MAKE_10_VV00(V) SPROUT_VERSION_NUMBER(((V) / 100) % 100, 0, 0)
#define SPROUT_PREDEF_MAKE_10_VVRR(V) SPROUT_VERSION_NUMBER(((V) / 100) % 100, (V) % 100, 0)
#define SPROUT_PREDEF_MAKE_10_VVRRPP(V) SPROUT_VERSION_NUMBER(((V) / 10000) % 100, ((V) / 100) % 100, (V) % 100)
#define SPROUT_PREDEF_MAKE_10_VVRR0PP00(V) SPROUT_VERSION_NUMBER(((V) / 10000000) % 100, ((V) / 100000) % 100, ((V) / 100) % 100)
#define SPROUT_PREDEF_MAKE_10_VVRR0PPPP(V) SPROUT_VERSION_NUMBER(((V) / 10000000) % 100, ((V) / 100000) % 100, (V) % 10000)
#define SPROUT_PREDEF_MAKE_10_VVRR00PP00(V) SPROUT_VERSION_NUMBER(((V) / 100000000) % 100, ((V) / 1000000) % 100, ((V) / 100) % 100)

#define SPROUT_PREDEF_MAKE_DATE(Y, M, D) SPROUT_VERSION_NUMBER((Y) % 10000 - 1970, (M) % 100, (D) % 100)
#define SPROUT_PREDEF_MAKE_YYYYMMDD(V) SPROUT_PREDEF_MAKE_DATE(((V) / 10000) % 10000, ((V) / 100) % 100, (V) % 100)
#define SPROUT_PREDEF_MAKE_YYYY(V) SPROUT_PREDEF_MAKE_DATE(V, 1, 1)
#define SPROUT_PREDEF_MAKE_YYYYMM(V) SPROUT_PREDEF_MAKE_DATE((V) / 100, (V) % 100, 1)

#endif	// #ifndef SPROUT_PREDEF_MAKE_HPP
