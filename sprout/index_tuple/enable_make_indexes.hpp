/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// enable_make_indexes
	//
	template<typename IndexTupleType>
	struct enable_make_indexes
		: public IndexTupleType::type
	{
	public:
		typedef typename IndexTupleType::type type;
	public:
		static SPROUT_CONSTEXPR type make() {
			return type();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP
