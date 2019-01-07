/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_PPC_HPP
#define SPROUT_PREDEF_ARCHITECTURE_PPC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_PPC 0

#if defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) \
	|| defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || defined(_XENON)
#	undef SPROUT_ARCH_PPC
#	if !defined (SPROUT_ARCH_PPC) && (defined(__ppc601__) || defined(_ARCH_601))
#		define SPROUT_ARCH_PPC SPROUT_VERSION_NUMBER(6, 1, 0)
#	endif
#	if !defined (SPROUT_ARCH_PPC) && (defined(__ppc603__) || defined(_ARCH_603))
#		define SPROUT_ARCH_PPC SPROUT_VERSION_NUMBER(6, 3, 0)
#	endif
#	if !defined (SPROUT_ARCH_PPC) && (defined(__ppc604__) || defined(__ppc604__))
#		define SPROUT_ARCH_PPC SPROUT_VERSION_NUMBER(6, 4, 0)
#	endif
#	if !defined (SPROUT_ARCH_PPC)
#		define SPROUT_ARCH_PPC 1
#	endif
#endif

#if SPROUT_ARCH_PPC
#	define SPROUT_ARCH_PPC_AVAILABLE
#endif

#define SPROUT_ARCH_PPC_NAME "PowerPC"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_PPC_HPP
