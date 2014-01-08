/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_CAT_HPP
#define SPROUT_PREPROCESSOR_CAT_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_CAT
//
#define SPROUT_PP_CAT(a, b) SPROUT_PP_CAT_I(a, b)
#define SPROUT_PP_CAT_I(a, b) a ## b

#endif	// #ifndef SPROUT_PREPROCESSOR_CAT_HPP
