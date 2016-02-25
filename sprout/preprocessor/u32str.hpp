/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_U32STR_HPP
#define SPROUT_PREPROCESSOR_U32STR_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U32STR
//
#define SPROUT_PP_U32STR(str) SPROUT_PP_U32STR_I(str)
#define SPROUT_PP_U32STR_I(str) U ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U32STR_HPP
