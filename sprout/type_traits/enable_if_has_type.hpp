/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ENABLE_IF_HAS_TYPE_HPP
#define SPROUT_TYPE_TRAITS_ENABLE_IF_HAS_TYPE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// enable_if_has_type
	//
	template<typename T, typename R = void>
	struct enable_if_has_type {
	public:
		typedef R type;
	};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename R = void>
	using enable_if_has_type_t = typename sprout::enable_if_has_type<T, R>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ENABLE_IF_HAS_TYPE_HPP
