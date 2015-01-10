/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_TYPE_TRAITS_HPP
#define SPROUT_SUB_ARRAY_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_sub_array
	//
	template<typename T>
	struct is_sub_array
		: public sprout::false_type
	{};
	template<typename T>
	struct is_sub_array<T const>
		: public sprout::is_sub_array<T>
	{};
	template<typename T>
	struct is_sub_array<T const volatile>
		: public sprout::is_sub_array<T>
	{};
	template<typename Container>
	struct is_sub_array<sprout::sub_array<Container> >
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_sub_array_v = sprout::is_sub_array<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_TYPE_TRAITS_HPP
