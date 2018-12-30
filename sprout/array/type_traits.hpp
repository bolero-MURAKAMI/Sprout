/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ARRAY_TYPE_TRAITS_HPP
#define SPROUT_ARRAY_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_array_class
	//
	template<typename T>
	struct is_array_class
		: public sprout::false_type
	{};
	template<typename T>
	struct is_array_class<T const>
		: public sprout::is_array_class<T>
	{};
	template<typename T>
	struct is_array_class<T const volatile>
		: public sprout::is_array_class<T>
	{};
	template<typename T, std::size_t N>
	struct is_array_class<sprout::array<T, N> >
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_array_class_v = sprout::is_array_class<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_TYPE_TRAITS_HPP
