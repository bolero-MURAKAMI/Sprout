/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
#define SPROUT_UTILITY_STRING_REF_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>

namespace sprout {
	//
	// string_ref
	// wstring_ref
	// u16string_ref
	// u32string_ref
	//
	typedef sprout::basic_string_ref<char> string_ref;
	typedef sprout::basic_string_ref<wchar_t> wstring_ref;
#if SPROUT_USE_UNICODE_LITERALS
	typedef sprout::basic_string_ref<char16_t> u16string_ref;
	typedef sprout::basic_string_ref<char32_t> u32string_ref;
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
