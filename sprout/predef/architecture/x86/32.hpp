/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_ARCHITECTURE_X86_32_HPP
#define SPROUT_PREDEF_ARCHITECTURE_X86_32_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_ARCH_X86_32 0

#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) \
	|| defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
#	undef SPROUT_ARCH_X86_32
#	if !defined(SPROUT_ARCH_X86_32) && defined(__I86__)
#		define SPROUT_ARCH_X86_32 SPROUT_VERSION_NUMBER(__I86__, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_X86_32) && defined(_M_IX86)
#		define SPROUT_ARCH_X86_32 SPROUT_PREDEF_MAKE_10_VV00(_M_IX86)
#	endif
#	if !defined(SPROUT_ARCH_X86_32) && defined(__i686__)
#		define SPROUT_ARCH_X86_32 SPROUT_VERSION_NUMBER(6, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_X86_32) && defined(__i586__)
#		define SPROUT_ARCH_X86_32 SPROUT_VERSION_NUMBER(5, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_X86_32) && defined(__i486__)
#		define SPROUT_ARCH_X86_32 SPROUT_VERSION_NUMBER(4, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_X86_32) && defined(__i386__)
#		define SPROUT_ARCH_X86_32 SPROUT_VERSION_NUMBER(3, 0, 0)
#	endif
#	if !defined(SPROUT_ARCH_X86_32)
#		define SPROUT_ARCH_X86_32 1
#	endif
#endif

#if SPROUT_ARCH_X86_32
#	define SPROUT_ARCH_X86_32_AVAILABLE
#endif

#define SPROUT_ARCH_X86_32_NAME "Intel x86-32"

#include <sprout/predef/architecture/x86.hpp>

#endif	// #ifndef SPROUT_PREDEF_ARCHITECTURE_X86_32_HPP
