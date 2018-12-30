/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SIZED_PIT_TYPE_TRAITS_HPP
#define SPROUT_SIZED_PIT_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/sized_pit/sized_pit.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_sized_pit
	//
	template<typename T>
	struct is_sized_pit
		: public sprout::false_type
	{};
	template<typename T>
	struct is_sized_pit<T const>
		: public sprout::is_sized_pit<T>
	{};
	template<typename T>
	struct is_sized_pit<T const volatile>
		: public sprout::is_sized_pit<T>
	{};
	template<typename Container>
	struct is_sized_pit<sprout::sized_pit<Container> >
		: public sprout::true_type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_sized_pit_v = sprout::is_sized_pit<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_SIZED_PIT_TYPE_TRAITS_HPP
