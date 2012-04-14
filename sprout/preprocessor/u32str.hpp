#ifndef SPROUT_PREPROCESSOR_U32STR_HPP
#define SPROUT_PREPROCESSOR_U32STR_HPP

#include <sprout/config.hpp>

//
// SPROUT_PP_U32STR
//
#define SPROUT_PP_U32STR(str) SPROUT_PP_U32STR_I(str)
#define SPROUT_PP_U32STR_I(str) U ## str

#endif	// #ifndef SPROUT_PREPROCESSOR_U32STR_HPP

