/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_TYPE_TRAITS_HPP
#define SPROUT_UTILITY_STRING_REF_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_basic_string_ref
	//
	template<typename T>
	struct is_basic_string_ref
		: public sprout::false_type
	{};
	template<typename T>
	struct is_basic_string_ref<T const>
		: public sprout::is_basic_string_ref<T>
	{};
	template<typename T>
	struct is_basic_string_ref<T const volatile>
		: public sprout::is_basic_string_ref<T>
	{};
	template<typename T, typename Traits>
	struct is_basic_string_ref<sprout::basic_string_ref<T, Traits> >
		: public sprout::true_type
	{};

	//
	// is_string_ref_of
	//
	template<typename T, typename Elem>
	struct is_string_ref_of
		: public sprout::false_type
	{};
	template<typename T, typename Elem>
	struct is_string_ref_of<T const, Elem>
		: public sprout::is_string_ref_of<T, Elem>
	{};
	template<typename T, typename Elem>
	struct is_string_ref_of<T const volatile, Elem>
		: public sprout::is_string_ref_of<T, Elem>
	{};
	template<typename T, typename Traits, typename Elem>
	struct is_string_ref_of<sprout::basic_string_ref<T, Traits>, Elem>
		: public sprout::true_type
	{};

	//
	// is_string_ref
	//
	template<typename T>
	struct is_string_ref
		: public sprout::is_string_ref_of<T, char>
	{};
	//
	// is_wstring_ref
	//
	template<typename T>
	struct is_wstring_ref
		: public sprout::is_string_ref_of<T, wchar_t>
	{};
	//
	// is_u16string_ref
	//
	template<typename T>
	struct is_u16string_ref
		: public sprout::is_string_ref_of<T, char16_t>
	{};
	//
	// is_u32string_ref
	//
	template<typename T>
	struct is_u32string_ref
		: public sprout::is_string_ref_of<T, char32_t>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_basic_string_ref_v = sprout::is_basic_string_ref<T>::value;
	template<typename T, typename Elem>
	SPROUT_STATIC_CONSTEXPR bool is_string_ref_of_v = sprout::is_string_ref_of<T, Elem>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_string_ref_v = sprout::is_string_ref<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_wstring_ref_v = sprout::is_wstring_ref<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u16string_ref_v = sprout::is_u16string_ref<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_u32string_ref_v = sprout::is_u32string_ref<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_TYPE_TRAITS_HPP
