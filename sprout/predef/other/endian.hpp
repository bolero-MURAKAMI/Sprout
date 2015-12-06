/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_OTHER_ENDIAN_HPP
#define SPROUT_PREDEF_OTHER_ENDIAN_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/c/gnu.hpp>
#include <sprout/predef/os/macos.hpp>
#include <sprout/predef/os/bsd.hpp>
#include <sprout/predef/os/android.hpp>

//
// SPROUT_ENDIAN_BIG_BYTE
// SPROUT_ENDIAN_BIG_WORD
// SPROUT_ENDIAN_LITTLE_BYTE
// SPROUT_ENDIAN_LITTLE_WORD
//
#define SPROUT_ENDIAN_BIG_BYTE 0
#define SPROUT_ENDIAN_BIG_WORD 0
#define SPROUT_ENDIAN_LITTLE_BYTE 0
#define SPROUT_ENDIAN_LITTLE_WORD 0

#if !SPROUT_ENDIAN_BIG_BYTE && !SPROUT_ENDIAN_BIG_WORD && !SPROUT_ENDIAN_LITTLE_BYTE && !SPROUT_ENDIAN_LITTLE_WORD
#	if SPROUT_LIB_C_GNU || SPROUT_OS_ANDROID
#		include <endian.h>
#	else
#		if SPROUT_OS_MACOS
#			include <machine/endian.h>
#		else
#			if SPROUT_OS_BSD
#				if SPROUT_OS_BSD_OPEN
#					include <machine/endian.h>
#				else
#					include <sys/endian.h>
#				endif
#			endif
#		endif
#	endif
#	if defined(__BYTE_ORDER)
#		if defined(__BIG_ENDIAN) && (__BYTE_ORDER == __BIG_ENDIAN)
#			undef SPROUT_ENDIAN_BIG_BYTE
#			define SPROUT_ENDIAN_BIG_BYTE 1
#		endif
#		if defined(__LITTLE_ENDIAN) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#			undef SPROUT_ENDIAN_LITTLE_BYTE
#			define SPROUT_ENDIAN_LITTLE_BYTE 1
#		endif
#		if defined(__PDP_ENDIAN) && (__BYTE_ORDER == __PDP_ENDIAN)
#			undef SPROUT_ENDIAN_LITTLE_WORD
#			define SPROUT_ENDIAN_LITTLE_WORD 1
#		endif
#	endif
#	if !defined(__BYTE_ORDER) && defined(_BYTE_ORDER)
#		if defined(_BIG_ENDIAN) && (_BYTE_ORDER == _BIG_ENDIAN)
#			undef SPROUT_ENDIAN_BIG_BYTE
#			define SPROUT_ENDIAN_BIG_BYTE 1
#		endif
#		if defined(_LITTLE_ENDIAN) && (_BYTE_ORDER == _LITTLE_ENDIAN)
#			undef SPROUT_ENDIAN_LITTLE_BYTE
#			define SPROUT_ENDIAN_LITTLE_BYTE 1
#		endif
#		if defined(_PDP_ENDIAN) && (_BYTE_ORDER == _PDP_ENDIAN)
#			undef SPROUT_ENDIAN_LITTLE_WORD
#			define SPROUT_ENDIAN_LITTLE_WORD 1
#		endif
#	endif
#endif

#if !SPROUT_ENDIAN_BIG_BYTE && !SPROUT_ENDIAN_BIG_WORD && !SPROUT_ENDIAN_LITTLE_BYTE && !SPROUT_ENDIAN_LITTLE_WORD
#	if (defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)) || (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) \
		|| defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__)
#		undef SPROUT_ENDIAN_BIG_BYTE
#		define SPROUT_ENDIAN_BIG_BYTE 1
#	endif
#endif

#if !SPROUT_ENDIAN_BIG_BYTE && !SPROUT_ENDIAN_BIG_WORD && !SPROUT_ENDIAN_LITTLE_BYTE && !SPROUT_ENDIAN_LITTLE_WORD
#	if (defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || (defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)) \
		|| defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
#		undef SPROUT_ENDIAN_LITTLE_BYTE
#		define SPROUT_ENDIAN_LITTLE_BYTE 1
#	endif
#endif

#if !SPROUT_ENDIAN_BIG_BYTE && !SPROUT_ENDIAN_BIG_WORD && !SPROUT_ENDIAN_LITTLE_BYTE && !SPROUT_ENDIAN_LITTLE_WORD
#	include <sprout/predef/architecture.hpp>
#	if SPROUT_ARCH_M68K || SPROUT_ARCH_PARISC || SPROUT_ARCH_SPARC || SPROUT_ARCH_SYS370 || SPROUT_ARCH_SYS390 || SPROUT_ARCH_Z
#		undef SPROUT_ENDIAN_BIG_BYTE
#		define SPROUT_ENDIAN_BIG_BYTE 1
#	endif
#	if SPROUT_ARCH_AMD64 || SPROUT_ARCH_IA64 || SPROUT_ARCH_X86 || SPROUT_ARCH_BLACKFIN
#		undef SPROUT_ENDIAN_LITTLE_BYTE
#		define SPROUT_ENDIAN_LITTLE_BYTE 1
#	endif
#endif

#if !SPROUT_ENDIAN_BIG_BYTE && !SPROUT_ENDIAN_BIG_WORD && !SPROUT_ENDIAN_LITTLE_BYTE && !SPROUT_ENDIAN_LITTLE_WORD
#	if SPROUT_ARCH_ARM
#		include <sprout/predef/os/windows.hpp>
#		if SPROUT_OS_WINDOWS
#			undef SPROUT_ENDIAN_LITTLE_BYTE
#			define SPROUT_ENDIAN_LITTLE_BYTE 1
#		endif
#	endif
#endif

//
// SPROUT_ENDIAN_BIG_BYTE_AVAILABLE
// SPROUT_ENDIAN_BIG_WORD_BYTE_AVAILABLE
// SPROUT_ENDIAN_LITTLE_BYTE_AVAILABLE
// SPROUT_ENDIAN_LITTLE_WORD_BYTE_AVAILABLE
//
#if SPROUT_ENDIAN_BIG_BYTE
#	define SPROUT_ENDIAN_BIG_BYTE_AVAILABLE
#endif
#if SPROUT_ENDIAN_BIG_WORD
#	define SPROUT_ENDIAN_BIG_WORD_BYTE_AVAILABLE
#endif
#if SPROUT_ENDIAN_LITTLE_BYTE
#	define SPROUT_ENDIAN_LITTLE_BYTE_AVAILABLE
#endif
#if SPROUT_ENDIAN_LITTLE_WORD
#	define SPROUT_ENDIAN_LITTLE_WORD_BYTE_AVAILABLE
#endif

//
// SPROUT_ENDIAN_BIG_BYTE_NAME
// SPROUT_ENDIAN_BIG_WORD_NAME
// SPROUT_ENDIAN_LITTLE_BYTE_NAME
// SPROUT_ENDIAN_LITTLE_WORD_NAME
//
#define SPROUT_ENDIAN_BIG_BYTE_NAME "Byte-Swapped Big-Endian"
#define SPROUT_ENDIAN_BIG_WORD_NAME "Word-Swapped Big-Endian"
#define SPROUT_ENDIAN_LITTLE_BYTE_NAME "Byte-Swapped Little-Endian"
#define SPROUT_ENDIAN_LITTLE_WORD_NAME "Word-Swapped Little-Endian"

#endif	// #ifndef SPROUT_PREDEF_OTHER_ENDIAN_HPP
