/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LANGUAGE_OBJC_HPP
#define SPROUT_PREDEF_LANGUAGE_OBJC_HPP

#include <sprout/config.hpp>

#define SPROUT_LANG_OBJC 0

#if defined(__OBJC__)
#	undef SPROUT_LANG_OBJC
#	define SPROUT_LANG_OBJC 1
#endif

#if SPROUT_LANG_OBJC
#	define SPROUT_LANG_OBJC_AVAILABLE
#endif

#define SPROUT_LANG_OBJC_NAME "Objective-C"

#endif	// #ifndef SPROUT_PREDEF_LANGUAGE_OBJC_HPP
