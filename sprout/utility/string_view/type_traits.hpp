/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_TYPE_TRAITS_HPP
#define SPROUT_UTILITY_STRING_VIEW_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_view/string_view.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_basic_string_view
	//
	template<typename T>
	struct is_basic_string_view
		: public sprout::false_type
	{};
	template<typename T>
	struct is_basic_string_view<T const>
		: public sprout::is_basic_string_view<T>
	{};
	template<typename T>
	struct is_basic_string_view<T const volatile>
		: public sprout::is_basic_string_view<T>
	{};
	template<typename T, typename Traits>
	struct is_basic_string_view<sprout::basic_string_view<T, Traits> >
		: public sprout::true_type
	{};

	//
	// is_string_view_of
	//
	template<typename T, typename Elem>
	struct is_string_view_of
		: public sprout::false_type
	{};
	template<typename T, typename Elem>
	struct is_string_view_of<T const, Elem>
		: public sprout::is_string_view_of<T, Elem>
	{};
	template<typename T, typename Elem>
	struct is_string_view_of<T const volatile, Elem>
		: public sprout::is_string_view_of<T, Elem>
	{};
	template<typename T, typename Traits, typename Elem>
	struct is_string_view_of<sprout::basic_string_view<T, Traits>, Elem>
		: public sprout::true_type
	{};

	//
	// is_string_view
	//
	template<typename T>
	struct is_string_view
		: public sprout::is_string_view_of<T, char>
	{};
	//
	// is_wstring_view
	//
	template<typename T>
	struct is_wstring_view
		: public sprout::is_string_view_of<T, wchar_t>
	{};
#if SPROUT_USE_UNICODE_LITERALS
	//
	// is_u16string_view
	//
	template<typename T>
	struct is_u16string_view
		: public sprout::is_string_view_of<T, char16_t>
	{};
	//
	// is_u32string_view
	//
	template<typename T>
	struct is_u32string_view
		: public sprout::is_string_view_of<T, char32_t>
	{};
#endif

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_basic_string_view_v = sprout::is_basic_string_view<T>::value;
	template<typename T, typename Elem>
	SPROUT_STATIC_CONSTEXPR bool is_string_view_of_v = sprout::is_string_view_of<T, Elem>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_string_view_v = sprout::is_string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_wstring_view_v = sprout::is_wstring_view<T>::value;
#if SPROUT_USE_UNICODE_LITERALS
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u16string_view_v = sprout::is_u16string_view<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u32string_view_v = sprout::is_u32string_view<T>::value;
#endif
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_TYPE_TRAITS_HPP
