/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_COMPAQ_HPP
#define SPROUT_PREDEF_COMPILER_COMPAQ_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_COMP_DEC 0

#if defined(__DECC) || defined(__DECCXX)
#	if !defined(SPROUT_COMP_DEC_DETECTION) && defined(__DECCXX_VER)
#		define SPROUT_COMP_DEC_DETECTION SPROUT_PREDEF_MAKE_10_VVRR0PP00(__DECCXX_VER)
#	endif
#	if !defined(SPROUT_COMP_DEC_DETECTION) && defined(__DECC_VER)
#		define SPROUT_COMP_DEC_DETECTION SPROUT_PREDEF_MAKE_10_VVRR0PP00(__DECC_VER)
#	endif
#	if !defined(SPROUT_COMP_DEC_DETECTION)
#		define SPROUT_COM_DEC_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_DEC_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_DEC_EMULATED SPROUT_COMP_DEC_DETECTION
#	else
#		undef SPROUT_COMP_DEC
#		define SPROUT_COMP_DEC SPROUT_COMP_DEC_DETECTION
#	endif
#	define SPROUT_COMP_DEC_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_DEC_NAME "Compaq C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_COMPAQ_HPP
