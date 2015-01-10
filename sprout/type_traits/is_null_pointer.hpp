/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define SPROUT_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_null_pointer
	//
	template<typename T>
	struct is_null_pointer
		: public sprout::false_type
	{};
	template<typename T>
	struct is_null_pointer<T const>
		: public sprout::is_null_pointer<T>
	{};
	template<typename T>
	struct is_null_pointer<T volatile>
		: public sprout::is_null_pointer<T>
	{};
	template<typename T>
	struct is_null_pointer<T const volatile>
		: public sprout::is_null_pointer<T>
	{};
	template<>
	struct is_null_pointer<std::nullptr_t>
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_null_pointer_v = sprout::is_null_pointer<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_NULL_POINTER_HPP
