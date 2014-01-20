/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
#define SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP

#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>

//
// SPROUT_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
//
#ifndef SPROUT_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#	if SPROUT_CLANG_OR_LATER(3, 4, 0)
#		define SPROUT_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT (1)
#	else
#		define SPROUT_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT (0)
#	endif
#endif

//
// SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
//
#ifndef SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#	if SPROUT_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#		define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base) base()
#	else
#		define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base)
#	endif
#endif

#endif	// #ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
