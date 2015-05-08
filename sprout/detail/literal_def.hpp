/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_LITERAL_DEF_HPP
#define SPROUT_DETAIL_LITERAL_DEF_HPP

#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/preprocessor/cat.hpp>

//
// SPROUT_LITERAL_STRING_DEF
//
#if SPROUT_USE_UNICODE_LITERALS
#	define SPROUT_LITERAL_STRING_DEF(NAME, STRING, LENGTH) \
		template<typename Elem> \
		struct NAME; \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, STRING, LENGTH, char); \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, SPROUT_PP_CAT(L, STRING), LENGTH, wchar_t); \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, SPROUT_PP_CAT(u, STRING), LENGTH, char16_t); \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, SPROUT_PP_CAT(U, STRING), LENGTH, char32_t); \
		template<typename Elem> \
		struct NAME {}
#else
#	define SPROUT_LITERAL_STRING_DEF(NAME, STRING, LENGTH) \
		template<typename Elem> \
		struct NAME; \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, STRING, LENGTH, char); \
		SPROUT_LITERAL_STRING_DEF_IMPL(NAME, SPROUT_PP_CAT(L, STRING), LENGTH, wchar_t); \
		template<typename Elem> \
		struct NAME {}
#endif
#define SPROUT_LITERAL_STRING_DEF_IMPL(NAME, STRING, LENGTH, ELEM) \
	template<> \
	struct NAME<ELEM> { \
	public: \
		SPROUT_STATIC_CONSTEXPR sprout::basic_string<ELEM, LENGTH> value \
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(STRING) \
			; \
	}; \
	SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<ELEM, LENGTH> NAME<ELEM>::value \
		SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(STRING)

//
// SPROUT_LITERAL_CHAR_DEF
//
#if SPROUT_USE_UNICODE_LITERALS
#	define SPROUT_LITERAL_CHAR_DEF(NAME, CHAR) \
		template<typename Elem> \
		struct NAME; \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, CHAR, char); \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, SPROUT_PP_CAT(L, CHAR), wchar_t); \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, SPROUT_PP_CAT(u, CHAR), char16_t); \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, SPROUT_PP_CAT(U, CHAR), char32_t); \
		template<typename Elem> \
		struct NAME {}
#else
#	define SPROUT_LITERAL_CHAR_DEF(NAME, CHAR) \
		template<typename Elem> \
		struct NAME; \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, CHAR, char); \
		SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, SPROUT_PP_CAT(L, CHAR), wchar_t); \
		template<typename Elem> \
		struct NAME {}
#endif
#define SPROUT_LITERAL_CHAR_DEF_IMPL(NAME, CHAR, ELEM) \
	template<> \
	struct NAME<ELEM> \
		: public sprout::integral_constant<ELEM, CHAR> \
	{}

#endif	// #ifndef SPROUT_DETAIL_LITERAL_DEF_HPP
