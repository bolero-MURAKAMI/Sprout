#ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
#define SPROUT_UTILITY_STRING_REF_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>

namespace sprout {
	//
	// string_ref
	//
	typedef sprout::basic_string_ref<char> string_ref;
	//
	// wstring_ref
	//
	typedef sprout::basic_string_ref<wchar_t> wstring_ref;
	//
	// u16string_ref
	//
	typedef sprout::basic_string_ref<char16_t> u16string_ref;
	//
	// u32string_ref
	//
	typedef sprout::basic_string_ref<char32_t> u32string_ref;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
