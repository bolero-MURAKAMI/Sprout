/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INTERNAL_HPP
#define SPROUT_CONTAINER_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/sub_container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// internal
		//
		template<typename Container>
		struct internal
			: public sprout::sub_container_traits<
				typename std::remove_reference<Container>::type
			>::template internal<Container>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_HPP
