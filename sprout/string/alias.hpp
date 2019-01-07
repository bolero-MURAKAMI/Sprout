/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_ALIAS_HPP
#define SPROUT_STRING_ALIAS_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_TEMPLATE_ALIASES
#	include <sprout/workaround/std/cstddef.hpp>
#	include <sprout/string/string.hpp>
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

namespace sprout {
#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// string
	// wstring
	// u16string
	// u32string
	//
	template<std::size_t N>
	using string = sprout::basic_string<char, N>;
	template<std::size_t N>
	using wstring = sprout::basic_string<wchar_t, N>;
#if SPROUT_USE_UNICODE_LITERALS
	template<std::size_t N>
	using u16string = sprout::basic_string<char16_t, N>;
	template<std::size_t N>
	using u32string = sprout::basic_string<char32_t, N>;
#endif
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_ALIAS_HPP
