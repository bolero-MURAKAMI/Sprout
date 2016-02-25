/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_PGI_HPP
#define SPROUT_PREDEF_COMPILER_PGI_HPP

#include <sprout/config.hpp>
#include <sprout/predef/version_number.hpp>

#define SPROUT_COMP_PGI 0

#if defined(__PGI)
#	if !defined(SPROUT_COMP_PGI_DETECTION) && (defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__))
#		define SPROUT_COMP_PGI_DETECTION SPROUT_VERSION_NUMBER(__PGIC__, __PGIC_MINOR__, __PGIC_PATCHLEVEL__)
#	endif
#	if !defined(SPROUT_COMP_PGI_DETECTION)
#		define SPROUT_COMP_PGI_DETECTION 1
#	endif
#endif

#ifdef SPROUT_COMP_PGI_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_PGI_EMULATED SPROUT_COMP_PGI_DETECTION
#	else
#		undef SPROUT_COMP_PGI
#		define SPROUT_COMP_PGI SPROUT_COMP_PGI_DETECTION
#	endif
#	define SPROUT_COMP_PGI_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_PGI_NAME "Portland Group C/C++"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_PGI_HPP
