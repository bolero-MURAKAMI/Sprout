/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREDEF_LANGUAGE_STDCPP_HPP
#define SPROUT_PREDEF_LANGUAGE_STDCPP_HPP

#include <sprout/config.hpp>
#include <sprout/predef/make.hpp>

#define SPROUT_LANG_STDCPP 0

#if defined(__cplusplus)
#	undef SPROUT_LANG_STDCPP
#	if (__cplusplus > 100)
#		define SPROUT_LANG_STDCPP SPROUT_PREDEF_MAKE_YYYYMM(__cplusplus)
#	else
#		define SPROUT_LANG_STDCPP 1
#	endif
#endif

#if SPROUT_LANG_STDCPP
#	define SPROUT_LANG_STDCPP_AVAILABLE
#endif

#define SPROUT_LANG_STDCPP_NAME "Standard C++"

#define SPROUT_LANG_STDCPPCLI 0

#if defined(__cplusplus_cli)
#	undef SPROUT_LANG_STDCPPCLI
#	if (__cplusplus_cli > 100)
#		define SPROUT_LANG_STDCPPCLI SPROUT_PREDEF_MAKE_YYYYMM(__cplusplus_cli)
#	else
#		define SPROUT_LANG_STDCPPCLI 1
#	endif
#endif

#if SPROUT_LANG_STDCPPCLI
#	define SPROUT_LANG_STDCPPCLI_AVAILABLE
#endif

#define SPROUT_LANG_STDCPPCLI_NAME "Standard C++/CLI"

#define SPROUT_LANG_STDECPP 0

#if defined(__embedded_cplusplus)
#	undef SPROUT_LANG_STDECPP
#	define SPROUT_LANG_STDECPP 1
#endif

#if SPROUT_LANG_STDECPP
#	define SPROUT_LANG_STDECPP_AVAILABLE
#endif

#define SPROUT_LANG_STDECPP_NAME "Standard Embedded C++"

#endif	// #ifndef SPROUT_PREDEF_LANGUAGE_STDCPP_HPP
