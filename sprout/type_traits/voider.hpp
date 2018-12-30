/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_VOIDER_HPP
#define SPROUT_TYPE_TRAITS_VOIDER_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// voider
	//
	template<typename...>
	struct voider {
	public:
		typedef void type;
	};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename...>
	using void_t = void;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_VOIDER_HPP
