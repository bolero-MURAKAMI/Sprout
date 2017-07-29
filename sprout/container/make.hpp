/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_MAKE_HPP
#define SPROUT_CONTAINER_MAKE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make
	//
	template<typename Container, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::container_construct_traits<Container>::copied_type
	make(Args&&... args) {
		return sprout::container_construct_traits<Container>::make(SPROUT_FORWARD(Args, args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_MAKE_HPP
