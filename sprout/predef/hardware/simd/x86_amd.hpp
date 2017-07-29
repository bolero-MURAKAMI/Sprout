/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_HARDWARE_SIMD_X86_AMD_HPP
#define SPROUT_PREDEF_HARDWARE_SIMD_X86_AMD_HPP

#include <sprout/config.hpp>
#include <sprout/predef/hardware/simd/x86_amd/versions.hpp>

#define SPROUT_HW_SIMD_X86_AMD 0

#undef SPROUT_HW_SIMD_X86_AMD
#if !defined(SPROUT_HW_SIMD_X86_AMD) && defined(__XOP__)
#	define SPROUT_HW_SIMD_X86_AMD SPROUT_HW_SIMD_X86_AMD_XOP_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86_AMD) && defined(__FMA4__)
#	define SPROUT_HW_SIMD_X86_AMD SPROUT_HW_SIMD_X86_AMD_FMA4_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86_AMD) && defined(__SSE4A__)
#	define SPROUT_HW_SIMD_X86_AMD SPROUT_HW_SIMD_X86_AMD_SSE4A_VERSION
#endif

#if !defined(SPROUT_HW_SIMD_X86_AMD)
#	define SPROUT_HW_SIMD_X86_AMD 0
#else
#	include <sprout/predef/hardware/simd/x86.h>
#	if SPROUT_HW_SIMD_X86 > SPROUT_HW_SIMD_X86_AMD
#		undef SPROUT_HW_SIMD_X86_AMD
#		define SPROUT_HW_SIMD_X86_AMD SPROUT_HW_SIMD_X86
#	endif
#	define SPROUT_HW_SIMD_X86_AMD_AVAILABLE
#endif

#define SPROUT_HW_SIMD_X86_AMD_NAME "x86 (AMD) SIMD"

#endif	// #ifndef SPROUT_PREDEF_HARDWARE_SIMD_X86_AMD_HPP
