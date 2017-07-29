/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LANGUAGE_STDC_HPP
#define SPROUT_PREDEF_LANGUAGE_STDC_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LANG_STDC 0

#if defined(__STDC__)
#	undef SPROUT_LANG_STDC
#	if defined(__STDC_VERSION__)
#		if (__STDC_VERSION__ > 100)
#			define SPROUT_LANG_STDC SPROUT_PREDEF_MAKE_YYYYMM(__STDC_VERSION__)
#		else
#			define SPROUT_LANG_STDC 1
#		endif
#	else
#		define SPROUT_LANG_STDC 1
#	endif
#endif

#if SPROUT_LANG_STDC
#	define SPROUT_LANG_STDC_AVAILABLE
#endif

#define SPROUT_LANG_STDC_NAME "Standard C"

#endif	// #ifndef SPROUT_PREDEF_LANGUAGE_STDC_HPP
