/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_EMPTY_HPP
#define SPROUT_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>

namespace sprout {
	//
	// empty
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	empty(Container const& cont) {
		return sprout::begin(cont) == sprout::end(cont);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_EMPTY_HPP
