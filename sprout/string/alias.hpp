#ifndef SPROUT_STRING_ALIAS_HPP
#define SPROUT_STRING_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/string.hpp>

#if SPROUT_USE_TEMPLATE_ALIASES

#include <cstddef>

namespace sprout {
	//
	// string
	//
	template<std::size_t N>
	using string = sprout::basic_string<char, N>;
	//
	// wstring
	//
	template<std::size_t N>
	using wstring = sprout::basic_string<wchar_t, N>;
	//
	// u16string
	//
	template<std::size_t N>
	using u16string = sprout::basic_string<char16_t, N>;
	//
	// u32string
	//
	template<std::size_t N>
	using u32string = sprout::basic_string<char32_t, N>;
}	// namespace sprout

#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#endif	// #ifndef SPROUT_STRING_ALIAS_HPP
