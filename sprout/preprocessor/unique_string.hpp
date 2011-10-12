#ifndef SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP
#define SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP

#include <sprout/config.hpp>
#include <sprout/preprocessor/stringize.hpp>

//
// SPROUT_PP_UNIQUE_STRING
//
#define SPROUT_PP_UNIQUE_STRING __DATE__ " " __TIME__ " : " __FILE__ "(" SPROUT_PP_STRINGIZE(__LINE__) ")"

#endif	// #ifndef SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP

