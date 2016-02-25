/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_REBIND_SIZE_HPP
#define SPROUT_CONTAINER_REBIND_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_transform_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// rebind_size
		//
		template<typename Container, typename sprout::container_traits<Container>::size_type Size>
		struct rebind_size
			: public sprout::container_transform_traits<Container>::template rebind_size<Size>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REBIND_SIZE_HPP
