/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
#define SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP

#include <sprout/config.hpp>

//
// SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
// SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_TRAIL
// SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_BODY
//
#ifdef SPROUT_WORKAROUND_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base) : base()
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_TRAIL(base) , base()
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_BODY {}
#else
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base)
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_TRAIL(base)
#	define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_BODY SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
#endif

#endif	// #ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
