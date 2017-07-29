/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP
#define SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// get_internal
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::containers::internal<Container>::type
	get_internal(Container&& cont) {
		typedef typename std::remove_reference<Container>::type container_type;
		return sprout::sub_container_traits<container_type>::get_internal(SPROUT_FORWARD(Container, cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP
