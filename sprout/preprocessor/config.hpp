/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_CONFIG_HPP
#define SPROUT_PREPROCESSOR_CONFIG_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_VARIADICS
//
#if !defined(SPROUT_PP_VARIADICS)
#	if defined(__GCCXML__) || defined(__CUDACC__) || defined(__PATHSCALE__) || defined(__DMC__) || defined(__CODEGEARC__) || defined(__BORLANDC__) || defined(__MWERKS__) || defined(__SUNPRO_CC) || (defined(__HP_aCC) && !defined(__EDG__)) || defined(__MRC__) || defined(__SC__) || defined(__IBMCPP__) || defined(__PGI)
#		define SPROUT_PP_VARIADICS 0
#	elif defined(__clang__)
#		define SPROUT_PP_VARIADICS 1
#	elif defined(_MSC_VER) && _MSC_VER >= 1400 && !defined(__EDG__)
#		if _MSC_VER >= 1400
#			define SPROUT_PP_VARIADICS 1
#			define SPROUT_PP_VARIADICS_MSVC 1
#		else
#			define SPROUT_PP_VARIADICS 0
#		endif
#	elif defined(__WAVE__) && __WAVE_HAS_VARIADICS__ || defined(__GNUC__) && __GXX_EXPERIMENTAL_CXX0X__
#		define SPROUT_PP_VARIADICS 1
#	elif !defined(__cplusplus) && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
#		define SPROUT_PP_VARIADICS 1
#	else
#		define SPROUT_PP_VARIADICS 0
#	endif
#elif !SPROUT_PP_VARIADICS + 1 < 2
#	undef SPROUT_PP_VARIADICS
#	define SPROUT_PP_VARIADICS 1
#	if (defined(_MSC_VER) && _MSC_VER >= 1400 && !(defined(__EDG__)) || defined(__GCCXML__) || defined(__CUDACC__) || defined(__PATHSCALE__) || defined(__clang__) || defined(__DMC__) || defined(__CODEGEARC__) || defined(__BORLANDC__) || defined(__MWERKS__) || defined(__SUNPRO_CC) || defined(__HP_aCC) || defined(__MRC__) || defined(__SC__) || defined(__IBMCPP__) || defined(__PGI))
#		define SPROUT_PP_VARIADICS_MSVC 1
#	endif
#else
#	undef SPROUT_PP_VARIADICS
#	define SPROUT_PP_VARIADICS 0
#endif

#endif	// #ifndef SPROUT_PREPROCESSOR_CONFIG_HPP
