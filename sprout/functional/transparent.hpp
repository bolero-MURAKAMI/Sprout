/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_TRANSPARENT_HPP
#define SPROUT_FUNCTIONAL_TRANSPARENT_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// transparent
	//
	template<typename T = void>
	struct transparent {
	public:
		typedef T is_transparent;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TRANSPARENT_HPP
