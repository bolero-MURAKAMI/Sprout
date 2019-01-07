/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_HARDWARE_SIMD_ARM_HPP
#define SPROUT_PREDEF_HARDWARE_SIMD_ARM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/hardware/simd/arm/versions.hpp>

#define SPROUT_HW_SIMD_ARM 0

#undef SPROUT_HW_SIMD_ARM
#if !defined(SPROUT_HW_SIMD_ARM) && (defined(__ARM_NEON__) || defined(__aarch64__) || defined (_M_ARM))
#	define SPROUT_HW_SIMD_ARM SPROUT_HW_SIMD_ARM_NEON_VERSION
#endif

#if !defined(SPROUT_HW_SIMD_ARM)
#	define SPROUT_HW_SIMD_ARM 0
#else
#	define SPROUT_HW_SIMD_ARM_AVAILABLE
#endif

#define SPROUT_HW_SIMD_ARM_NAME "ARM SIMD"

#endif	// #ifndef SPROUT_PREDEF_HARDWARE_SIMD_ARM_HPP
