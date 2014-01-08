/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_U16STR_HPP
#define SPROUT_PREPROCESSOR_U16STR_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U16STR
//
#define SPROUT_PP_U16STR(str) SPROUT_PP_U16STR_I(str)
#define SPROUT_PP_U16STR_I(str) u ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U16STR_HPP
