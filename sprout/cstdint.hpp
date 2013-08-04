#ifndef SPROUT_CSTDINT_HPP
#define SPROUT_CSTDINT_HPP

#include <climits>
#include <cstdint>
#include <sprout/config.hpp>

//
// SPROUT_INT[N]_C
// SPROUT_UINT[N]_C
//
#if defined(__clang__) && (__clang_major__ == 3 && __clang_minor__ == 2) && !defined(__STDC_CONSTANT_MACROS)
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
