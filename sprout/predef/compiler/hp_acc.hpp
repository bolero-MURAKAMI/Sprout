/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_HP_ACC_HPP
#define SPROUT_PREDEF_COMPILER_HP_ACC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_HPACC 0

#if defined(__HP_aCC)
#	if !defined(SPROUT_COMP_HPACC_DETECTION) && (__HP_aCC > 1)
#		define SPROUT_COMP_HPACC_DETECTION SPROUT_PREDEF_MAKE_10_VVRRPP(__HP_aCC)
#	endif
#	if !defined(SPROUT_COMP_HPACC_DETECTION)
#		define SPROUT_COMP_HPACC_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_HPACC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_HPACC_EMULATED SPROUT_COMP_HPACC_DETECTION
#	else
#		undef SPROUT_COMP_HPACC
#		define SPROUT_COMP_HPACC SPROUT_COMP_HPACC_DETECTION
#	endif
#	define SPROUT_COMP_HPACC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_HPACC_NAME "HP aC++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_HP_ACC_HPP
