/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_HARDWARE_SIMD_PPC_HPP
#define SPROUT_PREDEF_HARDWARE_SIMD_PPC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/hardware/simd/ppc/versions.hpp>

#define SPROUT_HW_SIMD_PPC 0

#undef SPROUT_HW_SIMD_PPC
#if !defined(SPROUT_HW_SIMD_PPC) && defined(__VECTOR4DOUBLE__)
#	define SPROUT_HW_SIMD_PPC SPROUT_HW_SIMD_PPC_QPX_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_PPC) && defined(__VSX__)
#	define SPROUT_HW_SIMD_PPC SPROUT_HW_SIMD_PPC_VSX_VERSION
#endif
#if !defined(SPROUT_HW_SIMD_PPC) && (defined(__ALTIVEC__) || defined(__VEC__))
#	define SPROUT_HW_SIMD_PPC SPROUT_HW_SIMD_PPC_VMX_VERSION
#endif

#if !defined(SPROUT_HW_SIMD_PPC)
#	define SPROUT_HW_SIMD_PPC 0
#else
#	define SPROUT_HW_SIMD_PPC_AVAILABLE
#endif

#define SPROUT_HW_SIMD_PPC_NAME "PPC SIMD"

#endif	// #ifndef SPROUT_PREDEF_HARDWARE_SIMD_PPC_HPP
