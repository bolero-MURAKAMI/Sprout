/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDINT_HPP
#define SPROUT_CSTDINT_HPP

#include <climits>
#include <cstdint>
#include <sprout/config.hpp>

//
// SPROUT_INT[N]_C
// SPROUT_UINT[N]_C
//
#ifndef INT8_C
#	define SPROUT_INT8_C(n) n
#else
#	define SPROUT_INT8_C(n) INT8_C(n)
#endif
#ifndef UINT8_C
#	define SPROUT_UINT8_C(n) n
#else
#	define SPROUT_UINT8_C(n) UINT8_C(n)
#endif
#ifndef INT16_C
#	define SPROUT_INT16_C(n) n
#else
#	define SPROUT_INT16_C(n) INT16_C(n)
#endif
#ifndef UINT16_C
#	define SPROUT_UINT16_C(n) n
#else
#	define SPROUT_UINT16_C(n) UINT16_C(n)
#endif
#ifndef INT32_C
#	if LONG_MAX == LLONG_MAX
#		define SPROUT_INT32_C(n) n
#	else
#		define SPROUT_INT32_C(n) n ## L
#	endif
#else
#	define SPROUT_INT32_C(n) INT32_C(n)
#endif
#ifndef UINT32_C
#	if LONG_MAX == LLONG_MAX
#		define SPROUT_UINT32_C(n) n ## U
#	else
#		define SPROUT_UINT32_C(n) n ## UL
#	endif
#else
#	define SPROUT_UINT32_C(n) UINT32_C(n)
#endif
#ifndef INT64_C
#	if LONG_MAX == LLONG_MAX
#		define SPROUT_INT64_C(n) n ## L
#	else
#		define SPROUT_INT64_C(n) n ## LL
#	endif
#else
#	define SPROUT_INT64_C(n) INT64_C(n)
#endif
#ifndef UINT64_C
#	if LONG_MAX == LLONG_MAX
#		define SPROUT_UINT64_C(n) n ## UL
#	else
#		define SPROUT_UINT64_C(n) n ## ULL
#	endif
#else
#	define SPROUT_UINT64_C(n) UINT64_C(n)
#endif

#endif	// #ifndef SPROUT_CSTDINT_HPP
