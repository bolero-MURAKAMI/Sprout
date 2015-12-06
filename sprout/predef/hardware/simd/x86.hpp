/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_HARDWARE_SIMD_X86_HPP
#define SPROUT_PREDEF_HARDWARE_SIMD_X86_HPP

#include <sprout/config.hpp>
#include <sprout/predef/hardware/simd/x86/versions.hpp>

#define SPROUT_HW_SIMD_X86 0

#undef SPROUT_HW_SIMD_X86
#if !defined(SPROUT_HW_SIMD_X86) && defined(__MIC__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_MIC_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__AVX2__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_AVX2_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__AVX__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_AVX_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__FMA__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_FMA_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__SSE4_2__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSE4_2_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__SSE4_1__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSE4_1_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__SSSE3__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSSE3_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__SSE3__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSE3_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && (defined(__SSE2__) || defined(_M_X64) || _M_IX86_FP >= 2)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSE2_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && (defined(__SSE__) || defined(_M_X64) || _M_IX86_FP >= 1)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_SSE_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_X86) && defined(__MMX__)
#	define SPROUT_HW_SIMD_X86 SPROUT_HW_SIMD_X86_MMX_VERSION
#endif

#if !defined(SPROUT_HW_SIMD_X86)
#	define SPROUT_HW_SIMD_X86 0
#else
#	define SPROUT_HW_SIMD_X86_AVAILABLE
#endif

#define SPROUT_HW_SIMD_X86_NAME "x86 SIMD"

#endif	// #ifndef SPROUT_PREDEF_HARDWARE_SIMD_X86_HPP
