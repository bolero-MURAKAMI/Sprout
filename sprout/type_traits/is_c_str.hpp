/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_C_STR_HPP
#define SPROUT_TYPE_TRAITS_IS_C_STR_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_c_str
	//
	template<typename T>
	struct is_c_str
		: public sprout::false_type
	{};
	template<typename T>
	struct is_c_str<T const>
		: public sprout::is_c_str<T>
	{};
	template<typename T>
	struct is_c_str<T volatile>
		: public sprout::is_c_str<T>
	{};
	template<typename T>
	struct is_c_str<T const volatile>
		: public sprout::is_c_str<T>
	{};
	template<std::size_t N>
	struct is_c_str<char[N]>
		: public sprout::true_type
	{};
	template<std::size_t N>
	struct is_c_str<wchar_t[N]>
		: public sprout::true_type
	{};
#if SPROUT_USE_UNICODE_LITERALS
	template<std::size_t N>
	struct is_c_str<char16_t[N]>
		: public sprout::true_type
	{};
	template<std::size_t N>
	struct is_c_str<char32_t[N]>
		: public sprout::true_type
	{};
#endif

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_c_str_v = sprout::is_c_str<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_C_STR_HPP
