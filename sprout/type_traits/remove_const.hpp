/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_REMOVE_CONST_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// remove_const
	//
	using std::remove_const;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_const_t = typename sprout::remove_const<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_CONST_HPP
