/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CHAR_TYPE_HPP
#define SPROUT_TYPE_TRAITS_IS_CHAR_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_char_type
	//
	template<typename T>
	struct is_char_type
		: public sprout::false_type
	{};
	template<typename T>
	struct is_char_type<T const>
		: public sprout::is_char_type<T>
	{};
	template<typename T>
	struct is_char_type<T volatile>
		: public sprout::is_char_type<T>
	{};
	template<typename T>
	struct is_char_type<T const volatile>
		: public sprout::is_char_type<T>
	{};
	template<>
	struct is_char_type<char>
		: public sprout::true_type
	{};
	template<>
	struct is_char_type<wchar_t>
		: public sprout::true_type
	{};
	template<>
	struct is_char_type<char16_t>
		: public sprout::true_type
	{};
	template<>
	struct is_char_type<char32_t>
		: public sprout::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CHAR_TYPE_HPP
