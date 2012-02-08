#ifndef SPROUT_PREPROCESSOR_CAT_HPP
#define SPROUT_PREPROCESSOR_CAT_HPP

#include <sprout/config.hpp>

#define SPROUT_PP_CAT_I(a, b) a ## b

//
// SPROUT_PP_CAT
//
#define SPROUT_PP_CAT(a, b) SPROUT_PP_CAT_I(a, b)

#endif	// #ifndef SPROUT_PREPROCESSOR_CAT_HPP

