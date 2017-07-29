/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_SPARC_HPP
#define SPROUT_PREDEF_ARCHITECTURE_SPARC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_SPARC 0

#if defined(__sparc__) || defined(__sparc)
#	undef SPROUT_ARCH_SPARC
#	if !defined(SPROUT_ARCH_SPARC) && defined(__sparcv9)
#		define SPROUT_ARCH_SPARC SPROUT_VERSION_NUMBER(9, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SPARC) && defined(__sparcv8)
#		define SPROUT_ARCH_SPARC SPROUT_VERSION_NUMBER(8, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SPARC)
#		define SPROUT_ARCH_SPARC 1
#	endif
#endif

#if SPROUT_ARCH_SPARC
#	define SPROUT_ARCH_SPARC_AVAILABLE
#endif

#define SPROUT_ARCH_SPARC_NAME "SPARC"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_SPARC_HPP
