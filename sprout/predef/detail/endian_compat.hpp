/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_DETAIL_ENDIAN_COMPAT_HPP
#define SPROUT_PREDEF_DETAIL_ENDIAN_COMPAT_HPP

#include <sprout/config.hpp>
#include <sprout/predef/other/endian.hpp>

#if SPROUT_ENDIAN_BIG_BYTE
#	define SPROUT_BIG_ENDIAN
#	define SPROUT_BYTE_ORDER 4321
#endif
#if SPROUT_ENDIAN_LITTLE_BYTE
#	define SPROUT_LITTLE_ENDIAN
#	define SPROUT_BYTE_ORDER 1234
#endif
#if SPROUT_ENDIAN_LITTLE_WORD
#	define SPROUT_PDP_ENDIAN
#	define SPROUT_BYTE_ORDER 2134
#endif

#endif	// #ifndef SPROUT_PREDEF_HPP
