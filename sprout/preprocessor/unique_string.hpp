/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP
#define SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP

#include <sprout/config.hpp>
#include <sprout/preprocessor/stringize_all.hpp>
#include <sprout/preprocessor/str_all.hpp>

//
// SPROUT_PP_UNIQUE_STRING
// SPROUT_PP_UNIQUE_WSTRING
// SPROUT_PP_UNIQUE_U16STRING
// SPROUT_PP_UNIQUE_U32STRING
//
#define SPROUT_PP_UNIQUE_STRING __DATE__ " " __TIME__ " : " __FILE__ ":" SPROUT_PP_STRINGIZE(__LINE__)
#define SPROUT_PP_UNIQUE_WSTRING SPROUT_PP_WSTR(__DATE__) SPROUT_PP_WSTR(" ") SPROUT_PP_WSTR(__TIME__) \
	SPROUT_PP_WSTR(" : ") SPROUT_PP_WSTR(__FILE__) SPROUT_PP_WSTR(":") SPROUT_PP_WSTRINGIZE(__LINE__)
#define SPROUT_PP_UNIQUE_U16STRING SPROUT_PP_U16STR(__DATE__) SPROUT_PP_U16STR(" ") SPROUT_PP_U16STR(__TIME__) \
	SPROUT_PP_U16STR(" : ") SPROUT_PP_U16STR(__FILE__) SPROUT_PP_U16STR(":") SPROUT_PP_U16STRINGIZE(__LINE__)
#define SPROUT_PP_UNIQUE_U32STRING SPROUT_PP_U32STR(__DATE__) SPROUT_PP_U32STR(" ") SPROUT_PP_U32STR(__TIME__) \
	SPROUT_PP_U32STR(" : ") SPROUT_PP_U32STR(__FILE__) SPROUT_PP_U32STR(":") SPROUT_PP_U32STRINGIZE(__LINE__)

#endif	// #ifndef SPROUT_PREPROCESSOR_UNIQUE_STRING_HPP
