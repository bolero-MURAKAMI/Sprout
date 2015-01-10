/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CONST_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// remove_shallow_const
	//
	template<typename T>
	struct remove_shallow_const
		: public sprout::identity<T>
	{};
	template<typename T>
	struct remove_shallow_const<T const>
		: public std::conditional<std::is_array<T>::value, T const, T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_shallow_const_t = typename sprout::remove_shallow_const<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CONST_HPP
