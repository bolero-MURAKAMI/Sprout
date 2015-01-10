/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP
#define SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/internal_begin.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// internal_end_offset
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
	internal_end_offset(Container const& cont) {
		return sprout::distance(sprout::internal_begin(cont), sprout::end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP
