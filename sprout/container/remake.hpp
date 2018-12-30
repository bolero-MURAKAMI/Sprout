/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_REMAKE_HPP
#define SPROUT_CONTAINER_REMAKE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// remake
	//
	template<typename Container, typename Cont, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::container_construct_traits<Container>::copied_type
	remake(Cont&& cont, typename sprout::container_traits<Container>::difference_type size, Args&&... args) {
		return sprout::container_construct_traits<Container>::remake(
			SPROUT_FORWARD(Cont, cont),
			size,
			SPROUT_FORWARD(Args, args)...
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REMAKE_HPP
