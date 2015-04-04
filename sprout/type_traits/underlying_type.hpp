/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define SPROUT_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// underlying_type
	//
	using std::underlying_type;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using underlying_type_t = typename sprout::underlying_type<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_UNDERLYING_TYPE_HPP
