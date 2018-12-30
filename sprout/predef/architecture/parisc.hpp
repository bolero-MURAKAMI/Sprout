/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_PARISC_HPP
#define SPROUT_PREDEF_ARCHITECTURE_PARISC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_PARISC 0

#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#	undef SPROUT_ARCH_PARISC
#	if !defined(SPROUT_ARCH_PARISC) && (defined(_PA_RISC1_0))
#		define SPROUT_ARCH_PARISC SPROUT_VERSION_NUMBER(1, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_PARISC) && (defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__))
#		define SPROUT_ARCH_PARISC SPROUT_VERSION_NUMBER(1, 1, 0)
#	endif
#	if !defined(SPROUT_ARCH_PARISC) && (defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__))
#		define SPROUT_ARCH_PARISC SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_PARISC)
#		define SPROUT_ARCH_PARISC 1
#	endif
#endif

#if SPROUT_ARCH_PARISC
#	define SPROUT_ARCH_PARISC_AVAILABLE
#endif

#define SPROUT_ARCH_PARISC_NAME "HP/PA RISC"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_PARISC_HPP
