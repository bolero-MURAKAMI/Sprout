/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDINT_HPP
#define SPROUT_CSTDINT_HPP

#include <climits>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>

//
// SPROUT_INT[N]_C
// SPROUT_UINT[N]_C
//
#if SPROUT_CLANG_BETWEEN((3, 0, 0), (3, 3, 0)) && !defined(__STDC_CONSTANT_MACROS)
#	define SPROUT_INT8_C(n) n
#	define SPROUT_UINT8_C(n) n
#	define SPROUT_INT16_C(n) n
#	define SPROUT_UINT16_C(n) n
#	if LONG_MAX == LLONG_MAX
#		define SPROUT_INT32_C(n) n
#		define SPROUT_UINT32_C(n) n ## U
#		define SPROUT_INT64_C(n) n ## UL
#		define SPROUT_UINT64_C(n) n ## UL
#	else
#		define SPROUT_INT32_C(n) n ## L
#		define SPROUT_UINT32_C(n) n ## UL
#		define SPROUT_INT64_C(n) n ## ULL
#		define SPROUT_UINT64_C(n) n ## ULL
#	endif
#else
#	define SPROUT_INT8_C(n) INT8_C(n)
#	define SPROUT_UINT8_C(n) UINT8_C(n)
#	define SPROUT_INT16_C(n) INT16_C(n)
#	define SPROUT_UINT16_C(n) UINT16_C(n)
#	define SPROUT_INT32_C(n) INT32_C(n)
#	define SPROUT_UINT32_C(n) UINT32_C(n)
#	define SPROUT_INT64_C(n) INT64_C(n)
#	define SPROUT_UINT64_C(n) UINT64_C(n)
#endif

#endif	// #ifndef SPROUT_CSTDINT_HPP
