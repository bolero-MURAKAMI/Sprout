/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_BACKWARD_HPP
#define SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/internal_end.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// internal_begin_offset_backward
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
	internal_begin_offset_backward(Container const& cont) {
		return sprout::distance(sprout::begin(cont), sprout::internal_end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_BACKWARD_HPP
