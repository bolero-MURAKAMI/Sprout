/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DECAY_HPP
#define SPROUT_TYPE_TRAITS_DECAY_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// decay
	//
	using std::decay;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using decay_t = typename sprout::decay<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_DECAY_HPP
