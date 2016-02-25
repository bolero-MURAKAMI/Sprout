/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_M68K_HPP
#define SPROUT_PREDEF_ARCHITECTURE_M68K_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_M68K 0

#if defined(__m68k__) || defined(M68000)
#	undef SPROUT_ARCH_M68K
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68060__) || defined(mc68060) || defined(__mc68060))
#		define SPROUT_ARCH_M68K SPROUT_VERSION_NUMBER(6, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68040__) || defined(mc68040) || defined(__mc68040))
#		define SPROUT_ARCH_M68K SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68030__) || defined(mc68030) || defined(__mc68030))
#		define SPROUT_ARCH_M68K SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68020__) || defined(mc68020) || defined(__mc68020))
#		define SPROUT_ARCH_M68K SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68010__) || defined(mc68010) || defined(__mc68010))
#		define SPROUT_ARCH_M68K SPROUT_VERSION_NUMBER(1, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_M68K) && (defined(__mc68000__) || defined(mc68000) || defined(__mc68000))
#		define SPROUT_ARCH_M68K 1
#	endif
#	if !defined(SPROUT_ARCH_M68K)
#		define SPROUT_ARCH_M68K 1
#	endif
#endif

#if SPROUT_ARCH_M68K
#	define SPROUT_ARCH_M68K_AVAILABLE
#endif

#define SPROUT_ARCH_M68K_NAME "Motorola 68k"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_M68K_HPP
