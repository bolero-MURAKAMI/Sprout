/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_STRING_REF_HPP
#define SPROUT_UTILITY_STRING_VIEW_STRING_REF_HPP

#include <sprout/config.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/utility/string_view/string_view.hpp>
#include <sprout/utility/string_view/type_traits.hpp>
#include <sprout/detail/udl_namespace.hpp>

namespace sprout {
	//
	// string_ref
	// wstring_ref
	// u16string_ref
	// u32string_ref
	//
	typedef sprout::basic_string_view<char> string_ref;
	typedef sprout::basic_string_view<wchar_t> wstring_ref;
#if SPROUT_USE_UNICODE_LITERALS
	typedef sprout::basic_string_view<char16_t> u16string_ref;
	typedef sprout::basic_string_view<char32_t> u32string_ref;
#endif

#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// basic_string_ref
	//
	template<typename T, typename Traits = sprout::char_traits<T> >
	using basic_string_ref = sprout::basic_string_view<T, Traits>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// to_string_ref
	//
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_view<T, Traits>
	to_string_ref(sprout::basic_string_view<T, Traits> const& s) {
		return sprout::to_string_view(s);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_view<T, Traits>
	to_string_ref(sprout::basic_string<T, N, Traits> const& s) {
		return sprout::to_string_view(s);
	}
	template<typename T, typename Traits>
	inline SPROUT_NON_CONSTEXPR sprout::basic_string_view<T, Traits>
	to_string_ref(std::basic_string<T, Traits> const& s) {
		return sprout::to_string_view(s);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_view<T>
	to_string_ref(T const* str) {
		return sprout::to_string_view(str);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_view<T>
	to_string_ref(T const* str, std::size_t len) {
		return sprout::to_string_view(str, len);
	}

	//
	// is_basic_string_ref
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_basic_string_ref = sprout::is_basic_string_view<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	struct is_basic_string_ref
		: public sprout::is_basic_string_view<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// is_string_ref_of
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	using is_string_ref_of = sprout::is_string_view_of<T, Elem>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_string_ref_of
		: public sprout::is_string_view_of<T, Elem>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// is_string_ref
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_string_ref = sprout::is_string_view<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_string_ref
		: public sprout::is_string_view<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	//
	// is_wstring_ref
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_wstring_ref = sprout::is_wstring_view<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_wstring_ref
		: public sprout::is_wstring_view<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_UNICODE_LITERALS
	//
	// is_u16string_ref
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_u16string_ref = sprout::is_u16string_view<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_u16string_ref
		: public sprout::is_u16string_view<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	//
	// is_u32string_ref
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_u32string_ref = sprout::is_u32string_view<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_u32string_ref
		: public sprout::is_u32string_view<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
#endif

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_basic_string_ref_v = sprout::is_basic_string_view<T>::value;
	template<typename T, typename Elem>
	SPROUT_STATIC_CONSTEXPR bool is_string_ref_of_v = sprout::is_string_view_of<T, Elem>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_string_ref_v = sprout::is_string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_wstring_ref_v = sprout::is_wstring_view<T>::value;
#if SPROUT_USE_UNICODE_LITERALS
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u16string_ref_v = sprout::is_u16string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u32string_ref_v = sprout::is_u32string_view<T>::value;
#endif
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

	namespace literals {
		namespace strings {
			//
			// _sr
			//
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char>
			operator"" _sr(char const* s, std::size_t size) {
				return sprout::basic_string_view<char>(s, size);
			}
			inline SPROUT_CONSTEXPR sprout::basic_string_view<wchar_t>
			operator"" _sr(wchar_t const* s, std::size_t size) {
				return sprout::basic_string_view<wchar_t>(s, size);
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char16_t>
			operator"" _sr(char16_t const* s, std::size_t size) {
				return sprout::basic_string_view<char16_t>(s, size);
			}
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char32_t>
			operator"" _sr(char32_t const* s, std::size_t size) {
				return sprout::basic_string_view<char32_t>(s, size);
			}
#endif
		}	// namespace strings

		using sprout::literals::strings::operator"" _sr;
	}	// namespace literals

	using sprout::literals::strings::operator"" _sr;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_STRING_REF_HPP
