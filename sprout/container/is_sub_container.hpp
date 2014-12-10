/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP
#define SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace containers {
		//
		// is_sub_container
		//
		template<typename Container>
		struct is_sub_container
			: public sprout::bool_constant<
				!std::is_same<typename sprout::containers::internal<Container>::type, Container&&>::value
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP
