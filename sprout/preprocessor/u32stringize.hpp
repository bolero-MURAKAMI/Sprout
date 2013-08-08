/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_U32STRINGIZE_HPP
#define SPROUT_PREPROCESSOR_U32STRINGIZE_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U32STRINGIZE
//
#define SPROUT_PP_U32STRINGIZE(text) SPROUT_PP_U32STRINGIZE_I(text)
#define SPROUT_PP_U32STRINGIZE_I(text) SPROUT_PP_U32STRINGIZE_II(#text)
#define SPROUT_PP_U32STRINGIZE_II(str) U ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U32STRINGIZE_HPP
