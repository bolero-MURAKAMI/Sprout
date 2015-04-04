/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define SPROUT_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// make_unsigned
	//
	using std::make_unsigned;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using make_unsigned_t = typename sprout::make_unsigned<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_MAKE_UNSIGNED_HPP
