/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_ALIAS_HPP
#define SPROUT_UTILITY_STRING_VIEW_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_view/string_view.hpp>

namespace sprout {
	//
	// string_view
	// wstring_view
	// u16string_view
	// u32string_view
	//
	typedef sprout::basic_string_view<char> string_view;
	typedef sprout::basic_string_view<wchar_t> wstring_view;
#if SPROUT_USE_UNICODE_LITERALS
	typedef sprout::basic_string_view<char16_t> u16string_view;
	typedef sprout::basic_string_view<char32_t> u32string_view;
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_ALIAS_HPP
