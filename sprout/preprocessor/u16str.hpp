#ifndef SPROUT_PREPROCESSOR_U16STR_HPP
#define SPROUT_PREPROCESSOR_U16STR_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U16STR
//
#define SPROUT_PP_U16STR(str) SPROUT_PP_U16STR_I(str)
#define SPROUT_PP_U16STR_I(str) u ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U16STR_HPP

