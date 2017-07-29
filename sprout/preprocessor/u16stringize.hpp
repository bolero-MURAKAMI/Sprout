/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_U16STRINGIZE_HPP
#define SPROUT_PREPROCESSOR_U16STRINGIZE_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U16STRINGIZE
//
#define SPROUT_PP_U16STRINGIZE(text) SPROUT_PP_U16STRINGIZE_I(text)
#define SPROUT_PP_U16STRINGIZE_I(text) SPROUT_PP_U16STRINGIZE_II(#text)
#define SPROUT_PP_U16STRINGIZE_II(str) u ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U16STRINGIZE_HPP
