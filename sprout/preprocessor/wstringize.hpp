/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_WSTRINGIZE_HPP
#define SPROUT_PREPROCESSOR_WSTRINGIZE_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_WSTRINGIZE
//
#define SPROUT_PP_WSTRINGIZE(text) SPROUT_PP_WSTRINGIZE_I(text)
#define SPROUT_PP_WSTRINGIZE_I(text) SPROUT_PP_WSTRINGIZE_II(#text)
#define SPROUT_PP_WSTRINGIZE_II(str) L ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_WSTRINGIZE_HPP
