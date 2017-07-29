/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONFIG_STDLIB_HPP
#define SPROUT_CONFIG_STDLIB_HPP

// for STLport
// !!! OLD:
//#ifdef __cplusplus
//#	include <cstddef>
//#else
//#	include <stddef.h>
//#endif
#ifdef __cplusplus
#	include <climits>
#else
#	include <limits.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#	include <sprout/config/stdlib/stlport.hpp>
#else

#if !defined(__LIBCOMO__) && !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER) \
	&& !defined(_LIBCPP_VERSION) && !defined(__GLIBCPP__) && !defined(__GLIBCXX__) \
	&& !defined(__STL_CONFIG_H) && !defined(__MSL_CPP__) && !defined(__IBMCPP__) \
	&& !defined(MSIPL_COMPILE_H) && !defined(_YVALS) && !defined(_CPPLIB_VER)
#	include <utility>
#endif

#	if defined(__LIBCOMO__)
#		include <sprout/config/stdlib/libcomo.hpp>
#	elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#		include <sprout/config/stdlib/roguewave.hpp>
#	elif defined(_LIBCPP_VERSION)
#		include <sprout/config/stdlib/libcpp.hpp>
#	elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#		include <sprout/config/stdlib/libstdcpp3.hpp>
#	elif defined(__STL_CONFIG_H)
#		include <sprout/config/stdlib/sgi.hpp>
#	elif defined(__MSL_CPP__)
#		include <sprout/config/stdlib/msl.hpp>
#	elif defined(__IBMCPP__)
#		include <sprout/config/stdlib/vacpp.hpp>
#	elif defined(MSIPL_COMPILE_H)
#		include <sprout/config/stdlib/modena.hpp>
#	elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
#		include <sprout/config/stdlib/dinkumware.hpp>
#	endif
#endif

#endif	// #ifndef SPROUT_CONFIG_STDLIB_HPP
