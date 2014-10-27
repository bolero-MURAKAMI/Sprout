/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CHAR_LITERAL_HPP
#define SPROUT_DETAIL_CHAR_LITERAL_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/preprocessor/cat.hpp>

namespace sprout {
	namespace detail {
#if SPROUT_USE_UNICODE_LITERALS
		template<typename Elem, char C, wchar_t WC, char16_t C16, char32_t C32>
		struct char_literal_of;
		template<char C, wchar_t WC, char16_t C16, char32_t C32>
		struct char_literal_of<char, C, WC, C16, C32>
			: public sprout::integral_constant<char, C>
		{};
		template<char C, wchar_t WC, char16_t C16, char32_t C32>
		struct char_literal_of<wchar_t, C, WC, C16, C32>
			: public sprout::integral_constant<wchar_t, WC>
		{};
		template<char C, wchar_t WC, char16_t C16, char32_t C32>
		struct char_literal_of<char16_t, C, WC, C16, C32>
			: public sprout::integral_constant<char16_t, C16>
		{};
		template<char C, wchar_t WC, char16_t C16, char32_t C32>
		struct char_literal_of<char32_t, C, WC, C16, C32>
			: public sprout::integral_constant<char32_t, C32>
		{};
#else
		template<typename Elem, char C, wchar_t WC>
		struct char_literal_of;
		template<char C, wchar_t WC>
		struct char_literal_of<char, C, WC>
			: public sprout::integral_constant<char, C>
		{};
		template<char C, wchar_t WC>
		struct char_literal_of<wchar_t, C, WC>
			: public sprout::integral_constant<wchar_t, WC>
		{};
#endif
	}	// namespace detail
}	// namespace sprout

//
// SPROUT_CHAR_LITERAL
//
#if SPROUT_USE_UNICODE_LITERALS
#	define SPROUT_CHAR_LITERAL(CHAR, TYPE) \
		(sprout::detail::char_literal_of<TYPE, CHAR, SPROUT_PP_CAT(L, CHAR), SPROUT_PP_CAT(u, CHAR), SPROUT_PP_CAT(U, CHAR)>::value)
#else
#	define SPROUT_CHAR_LITERAL(CHAR, TYPE) \
		(sprout::detail::char_literal_of<TYPE, CHAR, SPROUT_PP_CAT(L, CHAR)>::value)
#endif

#endif	// #ifndef SPROUT_DETAIL_CHAR_LITERAL_HPP
