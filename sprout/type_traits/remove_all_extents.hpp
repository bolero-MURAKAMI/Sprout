/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// remove_all_extents
	//
	using std::remove_all_extents;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_all_extents_t = typename sprout::remove_all_extents<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
