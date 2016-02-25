/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_WSTR_HPP
#define SPROUT_PREPROCESSOR_WSTR_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_WSTR
//
#define SPROUT_PP_WSTR(str) SPROUT_PP_WSTR_I(str)
#define SPROUT_PP_WSTR_I(str) L ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_WSTR_HPP
