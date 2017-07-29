/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ADD_CONST_HPP
#define SPROUT_TYPE_TRAITS_ADD_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// add_const
	//
	using std::add_const;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using add_const_t = typename sprout::add_const<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ADD_CONST_HPP
