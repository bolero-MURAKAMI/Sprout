/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_REBIND_TYPE_HPP
#define SPROUT_CONTAINER_REBIND_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_transform_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// rebind_type
		//
		template<typename Container, typename Type>
		struct rebind_type
			: public sprout::container_transform_traits<Container>::template rebind_type<Type>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REBIND_TYPE_HPP
