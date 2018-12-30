/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_TRAITS_FWD_HPP
#define SPROUT_CONTAINER_TRAITS_FWD_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// container_traits
	//
	template<typename Container>
	struct container_traits;

	//
	// container_range_traits
	//
	template<typename Container>
	struct container_range_traits;

	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits;

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits;

	//
	// container_fitness_traits
	//
	template<typename Container>
	struct container_fitness_traits;

	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_TRAITS_FWD_HPP
