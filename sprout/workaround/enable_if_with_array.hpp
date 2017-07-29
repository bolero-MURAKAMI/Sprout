/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_ENABLE_IF_WITH_ARRAY_HPP
#define SPROUT_WORKAROUND_ENABLE_IF_WITH_ARRAY_HPP

#include <type_traits>
#include <sprout/config.hpp>

//
// SPROUT_ENABLE_IF_WITH_ARRAY_IN_TEMPLATE_PARAMS
// SPROUT_ENABLE_IF_WITH_ARRAY_IN_PARAMS
//
#ifdef SPROUT_WORKAROUND_NO_DEFAULT_TEMPLATE_PARAMETERS_SFINAE_WITH_ARRAY
#	define SPROUT_ENABLE_IF_WITH_ARRAY_IN_TEMPLATE_PARAMS(EXPR)
#	define SPROUT_ENABLE_IF_WITH_ARRAY_IN_PARAMS(EXPR) , typename std::enable_if<(EXPR)>::type* = 0
#else
#	define SPROUT_ENABLE_IF_WITH_ARRAY_IN_TEMPLATE_PARAMS(EXPR) , typename = typename std::enable_if<(EXPR)>::type
#	define SPROUT_ENABLE_IF_WITH_ARRAY_IN_PARAMS(EXPR)
#endif

#endif	// #ifndef SPROUT_WORKAROUND_ENABLE_IF_WITH_ARRAY_HPP
