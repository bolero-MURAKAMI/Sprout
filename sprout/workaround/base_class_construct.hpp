/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
#define SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP

#include <sprout/config.hpp>

//
// SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
//
#ifndef SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#	ifdef SPROUT_WORKAROUND_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
#		define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base) base()
#	else
#		define SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(base)
#	endif
#endif

#endif	// #ifndef SPROUT_WORKAROUND_BASE_CLASS_CONSTRUCT_HPP
