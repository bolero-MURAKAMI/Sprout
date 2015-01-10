/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_FIXED_SIZE_HPP
#define SPROUT_CONTAINER_FIXED_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// fixed_size
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	fixed_size() {
		return sprout::container_traits<Container>::fixed_size();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_FIXED_SIZE_HPP
