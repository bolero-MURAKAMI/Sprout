/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LIBRARY_STD_ROGUEWAVE_HPP
#define SPROUT_PREDEF_LIBRARY_STD_ROGUEWAVE_HPP

#include <sprout/config.hpp>
#include <sprout/predef/library/std/prefix.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LIB_STD_RW 0

#if defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#	undef SPROUT_LIB_STD_RW
#	if defined(_RWSTD_VER)
#		if _RWSTD_VER < 0x010000
#			define SPROUT_LIB_STD_RW SPROUT_PREDEF_MAKE_0X_VVRRP(_RWSTD_VER)
#		else
#			define SPROUT_LIB_STD_RW SPROUT_PREDEF_MAKE_0X_VVRRPP(_RWSTD_VER)
#		endif
#	else
#		define SPROUT_LIB_STD_RW 1
#	endif
#endif

#if SPROUT_LIB_STD_RW
#	define SPROUT_LIB_STD_RW_AVAILABLE
#endif

#define SPROUT_LIB_STD_RW_NAME "Roguewave"

#endif	//#ifndef SPROUT_PREDEF_LIBRARY_STD_ROGUEWAVE_HPP
