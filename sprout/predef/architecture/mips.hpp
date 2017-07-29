/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_MIPS_HPP
#define SPROUT_PREDEF_ARCHITECTURE_MIPS_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_MIPS 0

#if defined(__mips__) || defined(__mips) || \
	defined(__MIPS__)
#	undef SPROUT_ARCH_MIPS
#	if !defined(SPROUT_ARCH_MIPS) && (defined(__mips))
#		define SPROUT_ARCH_MIPS SPROUT_VERSION_NUMBER(__mips, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_MIPS) && (defined(_MIPS_ISA_MIPS1) || defined(_R3000))
#		define SPROUT_ARCH_MIPS SPROUT_VERSION_NUMBER(1, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_MIPS) && (defined(_MIPS_ISA_MIPS2) || defined(__MIPS_ISA2__) || defined(_R4000))
#		define SPROUT_ARCH_MIPS SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_MIPS) && (defined(_MIPS_ISA_MIPS3) || defined(__MIPS_ISA3__))
#		define SPROUT_ARCH_MIPS SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_MIPS) && (defined(_MIPS_ISA_MIPS4) || defined(__MIPS_ISA4__))
#		define SPROUT_ARCH_MIPS SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_MIPS)
#		define SPROUT_ARCH_MIPS 1
#	endif
#endif

#if SPROUT_ARCH_MIPS
#	define SPROUT_ARCH_MIPS_AVAILABLE
#endif

#define SPROUT_ARCH_MIPS_NAME "MIPS"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_MIPS_HPP
