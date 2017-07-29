/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define SPROUT_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// has_virtual_destructor
	//
	template<typename T>
	struct has_virtual_destructor
		: public sprout::detail::type_traits_wrapper<std::has_virtual_destructor<T> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool has_virtual_destructor_v = sprout::has_virtual_destructor<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
