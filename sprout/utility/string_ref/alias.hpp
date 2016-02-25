/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
#define SPROUT_UTILITY_STRING_REF_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>
#include <sprout/utility/string_ref/type_traits.hpp>

namespace sprout {
	//
	// string_ref
	// wstring_ref
	// u16string_ref
	// u32string_ref
	//
	typedef sprout::basic_string_ref<char> string_ref;
	typedef sprout::basic_string_ref<wchar_t> wstring_ref;
	typedef sprout::basic_string_ref<char16_t> u16string_ref;
	typedef sprout::basic_string_ref<char32_t> u32string_ref;
	//
	// string_view
	// wstring_view
	// u16string_view
	// u32string_view
	//
	typedef sprout::basic_string_ref<char> string_view;
	typedef sprout::basic_string_ref<wchar_t> wstring_view;
	typedef sprout::basic_string_ref<char16_t> u16string_view;
	typedef sprout::basic_string_ref<char32_t> u32string_view;

#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// basic_string_view
	//
	template<typename T, typename Traits = sprout::char_traits<T> >
	using basic_string_view = sprout::basic_string_ref<T, Traits>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// to_string_view
	//
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_view(sprout::basic_string_ref<T, Traits> const& s) {
		return sprout::to_string_ref(s);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_view(sprout::basic_string<T, N, Traits> const& s) {
		return sprout::to_string_ref(s);
	}
	template<typename T, typename Traits>
	inline SPROUT_NON_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_view(std::basic_string<T, Traits> const& s) {
		return sprout::to_string_ref(s);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T>
	to_string_view(T const* str) {
		return sprout::to_string_ref(str);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T>
	to_string_view(T const* str, std::size_t len) {
		return sprout::to_string_ref(str, len);
	}

	//
	// is_basic_string_view
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_basic_string_view = sprout::is_basic_string_ref<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	struct is_basic_string_view
		: public sprout::is_basic_string_ref<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// is_string_view_of
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	using is_string_view_of = sprout::is_string_ref_of<T, Elem>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_string_view_of
		: public sprout::is_string_ref_of<T, Elem>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

	//
	// is_string_view
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_string_view = sprout::is_string_ref<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_string_view
		: public sprout::is_string_ref<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	//
	// is_wstring_view
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_wstring_view = sprout::is_wstring_ref<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_wstring_view
		: public sprout::is_wstring_ref<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	//
	// is_u16string_view
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_u16string_view = sprout::is_u16string_ref<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_u16string_view
		: public sprout::is_u16string_ref<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	//
	// is_u32string_view
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_u32string_view = sprout::is_u32string_ref<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Elem>
	struct is_u32string_view
		: public sprout::is_u32string_ref<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_basic_string_view_v = sprout::is_basic_string_view<T>::value;
	template<typename T, typename Elem>
	SPROUT_STATIC_CONSTEXPR bool is_string_view_of_v = sprout::is_string_view_of<T, Elem>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_string_view_v = sprout::is_string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_wstring_view_v = sprout::is_wstring_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u16string_view_v = sprout::is_u16string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u32string_view_v = sprout::is_u32string_view<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_ALIAS_HPP
