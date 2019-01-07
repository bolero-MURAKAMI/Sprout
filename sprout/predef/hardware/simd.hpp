/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_HARDWARE_SIMD_HPP
#define SPROUT_PREDEF_HARDWARE_SIMD_HPP

#include <sprout/config.hpp>
#include <sprout/predef/hardware/simd/x86.hpp>
#include <sprout/predef/hardware/simd/x86_amd.hpp>
#include <sprout/predef/hardware/simd/arm.hpp>
#include <sprout/predef/hardware/simd/ppc.hpp>

#if defined(SPROUT_HW_SIMD_ARM_AVAILABLE) && defined(SPROUT_HW_SIMD_PPC_AVAILABLE) \
	|| defined(SPROUT_HW_SIMD_ARM_AVAILABLE) && defined(SPROUT_HW_SIMD_X86_AVAILABLE) \
	|| defined(SPROUT_HW_SIMD_PPC_AVAILABLE) && defined(SPROUT_HW_SIMD_X86_AVAILABLE)
#	error "Multiple SIMD architectures detected, this cannot happen!"
#endif

#if defined(SPROUT_HW_SIMD_X86_AVAILABLE)
#	define SPROUT_HW_SIMD SPROUT_HW_SIMD_X86
#endif

#if defined(SPROUT_HW_SIMD_X86_AMD_AVAILABLE)
#	define SPROUT_HW_SIMD SPROUT_HW_SIMD_X86_AMD
#endif

#if defined(SPROUT_HW_SIMD_ARM_AVAILABLE)
#	define SPROUT_HW_SIMD SPROUT_HW_SIMD_ARM
#endif

#if defined(SPROUT_HW_SIMD_PPC_AVAILABLE)
#	define SPROUT_HW_SIMD SPROUT_HW_SIMD_PPC
#endif

#if defined(SPROUT_HW_SIMD)
#	define SPROUT_HW_SIMD_AVAILABLE
#else
#	define SPROUT_HW_SIMD 0
#endif

#define SPROUT_HW_SIMD_NAME "Hardware SIMD"

#endif	// #ifndef SPROUT_PREDEF_HARDWARE_SIMD_HPP
