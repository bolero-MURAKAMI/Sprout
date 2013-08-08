/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FIXED_CONTAINER_INTERNAL_DEEP_COPY_HPP
#define SPROUT_FIXED_CONTAINER_INTERNAL_DEEP_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/deep_internal.hpp>
#include <sprout/container/deep_copy.hpp>
#include <sprout/container/get_deep_internal.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// internal_deep_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_construct_traits<
		typename std::remove_reference<
			typename sprout::containers::deep_internal<Container>::type
		>::type
	>::copied_type
	internal_deep_copy(Container&& cont) {
		return sprout::deep_copy(
			sprout::get_deep_internal(sprout::forward<Container>(cont))
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_INTERNAL_DEEP_COPY_HPP
