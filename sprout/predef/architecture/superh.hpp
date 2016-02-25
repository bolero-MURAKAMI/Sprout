/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_SUPERH_HPP
#define SPROUT_PREDEF_ARCHITECTURE_SUPERH_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_ARCH_SH 0

#if defined(__sh__)
#	undef SPROUT_ARCH_SH
#	if !defined(SPROUT_ARCH_SH) && (defined(__SH5__))
#		define SPROUT_ARCH_SH SPROUT_VERSION_NUMBER(5, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SH) && (defined(__SH4__))
#		define SPROUT_ARCH_SH SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SH) && (defined(__sh3__) || defined(__SH3__))
#		define SPROUT_ARCH_SH SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SH) && (defined(__sh2__))
#		define SPROUT_ARCH_SH SPROUT_VERSION_NUMBER(2, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SH) && (defined(__sh1__))
#		define SPROUT_ARCH_SH SPROUT_VERSION_NUMBER(1, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_SH)
#		define SPROUT_ARCH_SH 1
#	endif
#endif

#if SPROUT_ARCH_SH
#	define SPROUT_ARCH_SH_AVAILABLE
#endif

#define SPROUT_ARCH_SH_NAME "SuperH"

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_SUPERH_HPP
