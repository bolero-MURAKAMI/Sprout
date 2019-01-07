/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_LLVM_HPP
#define SPROUT_PREDEF_COMPILER_LLVM_HPP

#include <sprout/config.hpp>
#include <sprout/predef/compiler/clang.hpp>

#define SPROUT_COMP_LLVM 0

#if defined(__llvm__)
#	define SPROUT_COMP_LLVM_DETECTION 1
#endif

#ifdef SPROUT_COMP_LLVM_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_LLVM_EMULATED SPROUT_COMP_LLVM_DETECTION
#	else
#		undef SPROUT_COMP_LLVM
#		define SPROUT_COMP_LLVM SPROUT_COMP_LLVM_DETECTION
#	endif
#	define SPROUT_COMP_LLVM_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_LLVM_NAME "LLVM"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_LLVM_HPP
