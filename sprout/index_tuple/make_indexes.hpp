/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// make_indexes
	//
	template<typename Seq>
	inline SPROUT_CONSTEXPR typename Seq::type
	make_indexes() {
		return typename Seq::type();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
