/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_COMPILER_GCC_XML_HPP
#define SPROUT_PREDEF_COMPILER_GCC_XML_HPP

#include <sprout/config.hpp>

#define SPROUT_COMP_GCCXML 0

#if defined(__GCCXML__)
#	define SPROUT_COMP_GCCXML_DETECTION 1
#endif

#ifdef SPROUT_COMP_GCCXML_DETECTION
#	if defined(SPROUT_PREDEF_DETAIL_COMP_DETECTED)
#		define SPROUT_COMP_GCCXML_EMULATED SPROUT_COMP_GCCXML_DETECTION
#	else
#		undef SPROUT_COMP_GCCXML
#		define SPROUT_COMP_GCCXML SPROUT_COMP_GCCXML_DETECTION
#	endif
#	define SPROUT_COMP_GCCXML_AVAILABLE
#	include <sprout/predef/detail/comp_detected.hpp>
#endif

#define SPROUT_COMP_GCCXML_NAME "GCC XML"

#endif	//#ifndef SPROUT_PREDEF_COMPILER_GCC_XML_HPP
